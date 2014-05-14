var graph

function graphready(json){
  graph = eval("(" + json + ")");
  drawgraph(graph);
}

function cleargraph(){
  var svg = d3.select("svg");
  svg.selectAll("circle").remove();
  svg.selectAll("path").remove();
  svg.selectAll("text").remove();
}

function drawgraph(graph){
  // create svg
  var svg = d3.select("svg")
    .attr('width','100%')
    .attr('height','100%')
  // define arrow markers for graph links
  svg.append('svg:defs').append('svg:marker')
    .attr('id', 'end-arrow')
    .attr('viewBox', '0 0 10 10')
    .attr('refX', 10)
    .attr('refY', 5)
    .attr('markerWidth', 3)
    .attr('markerHeight', 3)
    .attr('orient', 'auto')
    .append('svg:path')
    .attr('d', 'M0,0L10,5L0,10')
    .attr('fill', '#999');
  var circleradius = 20;
  var width = $("svg").width();
  height = $("svg").height();
  var force = d3.layout.force()
    .charge(-120000)
    .linkDistance(100)
    .friction(0.1)
    .size([width, height]);

  var drag = force.drag()
    .on("dragstart",function(d){
      d3.select(this).classed("fixed", d.fixed = true);
    });

  force
    .nodes(graph.nodes)
    .links(graph.links)
    .gravity(3)
    .start();

  //draw node and text in node
  var node = svg.selectAll("nodediv")
    .data(graph.nodes)
    .enter()
    .append("g")
    .call(force.drag)
    .on("dblclick",function(d){
        //d3.select(this).classed("fixed", d.fixed = false);
        //alert(d.name);
        $('input#content').val(d.name);
        $('button#default').click();
      });

  var nodecircle = node
    .append("svg:circle")
    .attr("cx", function(d) { return d.x; })
    .attr("cy", function(d) { return d.y; })
    .attr("class", function(d){
      if(d.type == 1){
        return "entitynode"
      }
      else{
        return "classnode"
      }
    })
    .attr("r", circleradius)

  nodecircle.append("title")
    .text(function(d){return d.name;});


  var nodetext = node
    .append("svg:text")
    .attr("x", function(d) { return d.x; })
    .attr("y", function(d) { return d.y; })
    .attr("dy", ".35em")
    .attr("text-anchor", "middle")
    .text(function(d) { return d.name;});

  // draw line and text on line
  var link = svg.selectAll("linkdiv")
    .data(graph.links)
    .enter()
    .append("g")
    .call(force.drag);
  var linkline = link
    .append("svg:path")
    .style('marker-end', 'url(#end-arrow)')
    .attr("class", "link")
    .style("stroke-width",3)
    .attr('d',function(d){
      var deltaX = d.target.x - d.source.x,
      deltaY = d.target.y - d.source.y,
      dist = Math.sqrt(deltaX * deltaX + deltaY * deltaY),
      normX = deltaX / dist,
      normY = deltaY / dist,
      sourceX = d.source.x + (circleradius * normX),
      sourceY = d.source.y + (circleradius * normY),
      targetX = d.target.x - ((circleradius) * normX),
      targetY = d.target.y - ((circleradius) * normY);
      return 'M' + sourceX + ',' + sourceY + 'L' + targetX + ',' + targetY;
    });
  var linktext = link
    .append("text")
    .attr("x", function(d){return (d.source.x + d.target.x)/2;})
    .attr("y", function(d){return (d.source.y + d.target.y)/2;})
    .text(function(d){return d.name;});

  //deal animation
  force.on("tick", function() {
    linkline.attr('d',function(d){
      var deltaX = d.target.x - d.source.x,
      deltaY = d.target.y - d.source.y,
      dist = Math.sqrt(deltaX * deltaX + deltaY * deltaY),
      normX = deltaX / dist,
      normY = deltaY / dist,
      sourceX = d.source.x + (circleradius * normX),
      sourceY = d.source.y + (circleradius * normY),
      targetX = d.target.x - (circleradius * normX),
      targetY = d.target.y - (circleradius * normY);
      return 'M' + sourceX + ',' + sourceY + 'L' + targetX + ',' + targetY;
    })
    linktext.attr("x", function(d) { return (d.source.x + d.target.x) / 2;})
      .attr("y", function(d) { return (d.source.y + d.target.y) /2; });
    nodecircle.attr("cx", function(d) { return d.x; })
      .attr("cy", function(d) { return d.y; });
    nodetext.attr("x", function(d) { return d.x; })
      .attr("y", function(d) { return d.y; });
  });
}
