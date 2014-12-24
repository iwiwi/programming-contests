#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

S = "▽△※囗☆〇〒◎§◇"

while line = gets
  line.strip!

  line.length.times do |i|
    printf("%d", S.index(line[i]))
  end
  puts
end
