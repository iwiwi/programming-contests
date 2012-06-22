#!/usr/bin/env ruby

N = 250000

printf("%d %d %d %d %d\n", rand(1000000000), rand(1000000000), rand(1000000000), rand(1000000000), N)
N.times do
  printf("%d %d %d %d %d\n", rand(1000000000), rand(1000000000), rand(1000000000), rand(1000000000), rand(1000000000))
end
