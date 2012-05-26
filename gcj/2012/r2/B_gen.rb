T = 1
N = 1000

puts T
T.times do
  rs = (1..N).map{1 + (rand * 10).to_i}
  s = rs.map{|r| 3.14 * r * r}.inject{|a, b| a + b}
  w = h = Math.sqrt(s * 5).to_i

  printf("%d %d %d\n", N, w, h)

  puts rs.join(" ")
end
