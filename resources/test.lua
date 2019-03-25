math.randomseed(os.time())

function initialization()
  chromo = {}
  for i = 0, 10 do
    table.insert(chromo, math.random())
  end
  return chromo
end

function evaluation(chromo)
  local acum = 0.0
  for k, v in ipairs(chromo) do
    acum = acum + v
  end
  return acum
end

function selection(fitness, chromos)
end

function recombination(lhs, rhs)
  split = math.random(table.getn(lhs))
  child_1 = {}
  child_2 = {}
  if math.random() > 0.5 then
    return lhs, rhs
  end
  for i = 0, table.getn(lhs) do
    if i < split then
      table.insert(child_1, lhs[i])
      table.insert(child_2, rhs[i])
    else
      table.insert(child_1, rhs[i])
      table.insert(child_2, lhs[i])
    end
  end
  return child_1, child_2
end

function mutation(chromo)
  if math.random() > 0.1 then
    return chromo
  end
  for i = 0, table.getn(chromo) do
    if math.random() <= 0.5 then
      chromo[i] = math.random()
    end
  end
  return chromo
end

function replacement(fitness, old, new)
  return new
end

function swap(a, b)
  print(a,b)
  return b, a
end

function rand()
  return math.random()
end
