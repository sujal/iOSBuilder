# Rakefile for iOSBuilder
#

require 'rubygems'
require 'betabuilder'

BetaBuilder::Tasks.new do |config|
  config.target = "SingleTarget"
  config.configuration = "Ad\ Hoc"   
  config.auto_archive = true
  config.archive_path = File.expand_path("~/Library/Application Support/Developer/Shared/Archived Applications/")

  # configure deployment via TestFlight
  config.deploy_using(:testflight) do |tf|
    tf.api_token  = ""
    tf.team_token = ""
  end
end
