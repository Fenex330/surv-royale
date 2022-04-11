class SurvRoyale < Formula
  desc "Desktop clone of surviv.io written in C++"
  homepage "https://github.com/Fenex330/surv-royale"
  head "https://github.com/Fenex330/surv-royale.git", tag: "v0.1.0"
  license "MIT"
  version "0.1.0"

  depends_on "sfml"
  depends_on "parallel" => :build

  def install
    system "make", "release", "client", "server", "install"
  end
end
