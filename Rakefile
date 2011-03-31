# Rakefile for iOSBuilder
#

require 'rubygems'
require 'betabuilder'

module IOSBuilder
  class Tasks < ::Rake::TaskLib
    def initialize(targets = :all, default_configuration = "Ad Hoc")
      define
    end
    
    def define

      targets = `xcodebuild -list | sed '
      		/Targets:/,/^[[:space:]]*$/			!d
      		/Targets/					d
      		/^[[:space:]]*$/				d
      		s/^[[:space:]]*//
      		s/(.*)//
      		s/[[:space:]]*$//
      	'`.strip.split(/\n/)
    
      raw_configs = `xcodebuild -list | sed '
        		/Build Configurations:/,/^[[:space:]]*$/	!d
        		/Build Configurations/				d
        		/^[[:space:]]*$/				d
        		s/[[:space:]]*\([^[:space:]].*\).*/\1/
        		s/[[:space:]][(]Active[)]$//
        	'| perl -e '$a="";while(<>){$a.=$_;} $a=~s/\n/:/mg; print $a;'`.strip.split(/:\s*/)
    
      p targets
      p raw_configs

      targets.each do |target|
        raw_configs.each do |xconfig|
          
          namespace = case xconfig
          when "Ad Hoc" then :beta
          else
            xconfig.downcase.to_sym
          end

          BetaBuilder::Tasks.new(namespace) do |config|
            config.target = target
            config.configuration = xconfig
            config.auto_archive = true
            config.archive_path = File.expand_path("~/Library/Application Support/Developer/Shared/Archived Applications/")
            if xconfig == "Ad Hoc" or xconfig == "Beta"
              # configure deployment via TestFlight
              config.deploy_using(:testflight) do |tf|
                tf.api_token  = ""
                tf.team_token = ""
              end
            end
          end
        end
      end

    end

  end
end

IOSBuilder::Tasks.new

BetaBuilder::Tasks.new(:testing) do |config|
  config.target = "DoubleTargetXC4QA"
  config.configuration = "Debug"
  config.auto_archive = false
end

