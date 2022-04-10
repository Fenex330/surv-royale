class SurvRoyale < Formula
  desc "Desktop clone of surviv.io written in C++"
  homepage "https://github.com/Fenex330/surv-royale"
  url "https://github.com/Fenex330/surv-royale/archive/refs/tags/v0.0.1.tar.gz"
  sha256 "e2977edff3e1b855845230695839f16a055c6a952de2fbd9d7d9b733ca8629b6"
  license "MIT"
  head "https://github.com/Fenex330/surv-royale.git", branch: "master"
  #head "https://github.com/Fenex330/surv-royale.git", tag: "v0.0.1"
  #version "0.0.1"

  depends_on "sfml"
  #depends_on "parallel" => :build

  def install
    #system "git", "checkout", "v0.0.1"
    #system "make", "release", "client", "server"
    system "make"
    system "make", "install"
  end
end
