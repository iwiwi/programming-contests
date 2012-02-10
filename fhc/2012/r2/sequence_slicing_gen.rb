T = 20
N = 2000
K = 100000000
R = 1000000000

printf("%d\n", T)
T.times do
  printf("%d %d %d\n", N, K, R)
  puts (1..N).map{ 1 + rand(100000) }.join(" ")
end
