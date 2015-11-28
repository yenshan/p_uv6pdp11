#!/usr/bin/ruby

(ARGV[0] && ARGV[1]) || abort("usage: ruby bin2load.rb <a.out> <outfile>")

class LdaFile < File
  def write_dat(data)
    cksum = 0
    data.each do |d|
      write [d].pack("C")
      cksum += d
    end
    return cksum
  end
  def write_sec(saddr, data)
    return if data == nil || data.size <= 0
    write_sec_h saddr, data
  end
  def write_sec_h(saddr, data=[])
    cksum  = write_dat [1,0]
    cksum += write_dat [data.size+6].pack("v").unpack("C*")
    cksum += write_dat [saddr].pack("v").unpack("C*")
    cksum += write_dat data if data.size > 0
    cksum = -(cksum & 0xff)
    write [cksum].pack("C")
  end
end

fin  = File.open(ARGV[0],"r")
fout = LdaFile.open(ARGV[1], "w")

magic, text_sz, data_sz, bss_sz, syms_sz, entry_adr, unused, flag =
  fin.read(2*8).unpack("S*")

fout.write_sec entry_adr,                 fin.read(text_sz).unpack("C*")
fout.write_sec entry_adr+text_sz,         fin.read(data_sz).unpack("C*")
fout.write_sec entry_adr+text_sz+data_sz, Array.new(bss_sz, 0)
fout.write_sec_h entry_adr

fin.close
fout.close



