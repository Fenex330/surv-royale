class SurvRoyale < Formula
  desc "Desktop clone of surviv.io written in C++"
  homepage "https://github.com/Fenex330/surv-royale"
  url "https://github.com/Fenex330/surv-royale.git", :using => :git, :tag => 'v0.1.0'
  license "MIT"

  depends_on "sfml"
  depends_on "parallel" => :build

  def install
    system "make", "release", "client", "server"
    system "make", "install", "PREFIX=#{prefix}"
  end
end
