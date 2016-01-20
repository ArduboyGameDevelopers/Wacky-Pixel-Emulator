require 'pathname'

class PrjFile
  attr_reader :headers, :sources

  def initialize(base_dir)
    @base_dir = base_dir
    @headers = []
    @sources = []
  end

  def add_file(file)
    file_ext = File.extname file
    if file_ext == '.h'
      @headers.push file
    elsif file_ext == '.c' || file_ext == '.cpp'
      @sources.push file
    else
      raise "Unsupported project file: #{file}"
    end
  end

  def save(file)

    base_path = Pathname.new @base_dir
    file_path = Pathname.new file



  end

end