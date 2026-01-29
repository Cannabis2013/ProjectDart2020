function scoreValue(modId, point) {
  if (modId === "T")
    return 3 * point;
  else if (modId === "D")
    return 2 * point;
  else
    return point;
}

function sum(inputs){
  let scoreSum = 0;
  let input = null;
  for (var i = 0; i < inputs.length; i++) {
    input = inputs[i];
    scoreSum += scoreValue(input.modId, input.point);
  }
  return scoreSum
}
