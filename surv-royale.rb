class SurvRoyale < Formula
  desc "Desktop clone of surviv.io"
  homepage "https://github.com/Fenex330/surv-royale"
  url "https://github.com/Fenex330/surv-royale.git", :using => :git, :tag => 'v2'
  license "MIT"

  depends_on "sfml"
  depends_on "parallel" => :build

  def install
    system "make", "release", "client", "server"
    system "make", "install", "PREFIX=#{prefix}"
  end
end
