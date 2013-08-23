lines = []

while line = gets
  line.strip!
  lines.push(line) if line.length != 0
end

puts lines.sort[6]

