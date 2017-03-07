array = require("array")
a = array.new(100)
print(a)
print(array.size(a))
for i=1, 100 do
  array.set(a, i, 1/i)
end

print(array.get(a, 10))
