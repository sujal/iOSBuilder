# Rakefile for iOSBuilder
#

require 'rubygems'
require 'betabuilder'

module IOSBuilder
  class Tasks < ::Rake::TaskLib
    def initialize(targets = :all, default_configuration = "Ad Hoc", params = {})
      
      @targets = targets
      @default_configuration = default_configuration
      @params = params
      
      define
    end
    
    def create_betabuilder(namespace, target, xconfig, tfapi=nil, tfteam=nil)
      BetaBuilder::Tasks.new(namespace) do |config|
        config.target = target
        config.configuration = xconfig
        config.auto_archive = true
        config.archive_path = File.expand_path("~/Library/Application Support/Developer/Shared/Archived Applications/")
        if (xconfig == "Ad Hoc" or xconfig == "Beta") and ( !tfapi.nil? and !tfteam.nil? )
          # configure deployment via TestFlight
          config.deploy_using(:testflight) do |tf|
            tf.api_token  = tfapi
            tf.team_token = tfteam
          end
        end
      end
    end
    
    def define

      xtargets = `xcodebuild -list | sed '
      		/Targets:/,/^[[:space:]]*$/			!d
      		/Targets/					d
      		/^[[:space:]]*$/				d
      		s/^[[:space:]]*//
      		s/(.*)//
      		s/[[:space:]]*$//
      	'`.strip.split(/\n/)
    
      if @targets != :all
        
        xtargets = xtargets.select do |v|
          @targets.include?(v)
        end
        
      end
    
      raw_configs = `xcodebuild -list | sed '
        		/Build Configurations:/,/^[[:space:]]*$/	!d
        		/Build Configurations/				d
        		/^[[:space:]]*$/				d
        		s/[[:space:]]*\([^[:space:]].*\).*/\1/
        		s/[[:space:]][(]Active[)]$//
        	'| perl -e '$a="";while(<>){$a.=$_;} $a=~s/\n/:/mg; print $a;'`.strip.split(/:\s*/)
    
      p xtargets
      p raw_configs

      xtargets.each do |target|
        raw_configs.each do |xconfig|
          
          target_namespace = target.to_sym
          
          namespace = case xconfig
          when "Ad Hoc" then :beta
          else
            xconfig.downcase.to_sym
          end

          if xtargets.length == 1
            self.create_betabuilder(namespace, target, xconfig, @params[:tf_api_token], @params[:tf_team_token])
          else
            namespace(target_namespace) do
              self.create_betabuilder(namespace, target, xconfig, @params[:tf_api_token], @params[:tf_team_token])
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

