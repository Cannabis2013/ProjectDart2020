/*
  Manipulate input score
  */

function appendCharacter(character){
    var l = scoreViewTextEdit.length;
    scoreViewTextEdit.insert(l,character);
}

function takeLastCharacter() {
    var l = scoreViewTextEdit.length;
    scoreViewTextEdit.remove(l-1,l);
}
