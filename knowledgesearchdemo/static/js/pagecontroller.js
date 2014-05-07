function enter_pressed(e){
  var e = e || window.event;
  var btn = $('button#default');
  if(e.keyCode == 13){
    $('.press').attr("class","btn btn-default press");
    btn.attr("class","btn btn-info press");
    search($('#content').val(),btn.text());
  }
}
$(document).ready(function() {
  $('#waiting').hide();
});

$(window).resize(function(){
  cleargraph();
  drawgraph(graph);
});

$('.press').click(function(){
  $('.press').attr("class","btn btn-default press");
  $(this).attr("class","btn btn-info press");
  search($('input#content').val(),$(this).text());
});

$(window).resize(function(){
  if(typeof(graph) != "undefined"){
    cleargraph();
    drawgraph(graph);
  }
});

function search(content,type){
  cleargraph();
  if(content != ""){
    $('#waiting').show();
    Dajaxice.knowledgesearchapp.views.deal(changesearchmethod,{'content':content,'type':type});
  }
}

function changesearchmethod(data){
  $('#waiting').hide();
  Dajax.process(data);
}
