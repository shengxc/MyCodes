<!DOCTYPE html>
<meta charset="utf-8">
<style>
.node {
  stroke: #fff;
  stroke-width: 1.5px;
}
.link {
  stroke: #999;
  stroke-opacity: .6;
}
.text {
		  font-size: 11px;
		  pointer-events: none;
		}

</style>
<body>
<form name="infomation" action="demo.php" method="post">
  <p>实体1:<input type="text" name="entity1"/></p>
  <p>实体2:<input type="text" name="entity2"/></p>
  <p><input type="submit" name="submit"/></p>
</form>
<script src="./d3.v3.min.js"></script>
<script>
var circleradius = 30
var width = 960,
    height = 500;

var color = d3.scale.category20();

var force = d3.layout.force()
    .charge(-120)
    .linkDistance(160)
    .size([width, height]);

var svg = d3.select("body").append("svg")
    .attr("width", width)
    .attr("height", height);

// define arrow markers for graph links
svg.append('svg:defs').append('svg:marker')
    .attr('id', 'end-arrow')
    .attr('viewBox', '0 -5 10 10')
    .attr('refX', 6)
    .attr('markerWidth', 3)
    .attr('markerHeight', 3)
    .attr('orient', 'auto')
  .append('svg:path')
    .attr('d', 'M0,-5L10,0L0,5')
    .attr('fill', '#000');

svg.append('svg:defs').append('svg:marker')
    .attr('id', 'start-arrow')
    .attr('viewBox', '0 -5 10 10')
    .attr('refX', 4)
    .attr('markerWidth', 3)
    .attr('markerHeight', 3)
    .attr('orient', 'auto')
  .append('svg:path')
    .attr('d', 'M10,-5L0,0L10,5')
    .attr('fill', '#000');


d3.json("temp.json", function(error, graph) {
  force
    .nodes(graph.nodes)
    .links(graph.links)
    .start();

//draw node and text in node
  var node = svg.selectAll("nodediv")
      .data(graph.nodes)
      .enter()
      .append("g")
      .call(force.drag);

  var nodecircle = node
      .append("circle")
      .attr("cx", function(d) { return d.x; })
      .attr("cy", function(d) { return d.y; })
      .attr("class", "node")
      .attr("r", circleradius)
      .style("fill", function(d) { return color(d.type); })

  var nodetext = node
      .append("text")
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
      .append("path")
      .style('marker-end', 'url(#end-arrow)')
      .attr("class", "link")
      .style("stroke-width",3)
      .attr('d',function(d){
        var deltaX = d.target.x - d.source.x,
            deltaY = d.target.y - d.source.y,
            dist = Math.sqrt(deltaX * deltaX + deltaY * deltaY),
            normX = deltaX / dist,
            normY = deltaY / dist,
            sourcePadding = d.left ? 17 : 12,
            targetPadding = d.right ? 17 : 12,
            sourceX = d.source.x + (circleradius * normX),
            sourceY = d.source.y + (circleradius * normY),
            targetX = d.target.x - (circleradius * normX),
            targetY = d.target.y - (circleradius * normY);
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
            sourcePadding = d.left ? 17 : 12,
            targetPadding = d.right ? 17 : 12,
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
  });

</script>
<?php
/*if(isset($_POST["submit"]))
{
  require('vendor/autoload.php');
  $client = new Everyman\Neo4j\Client('localhost', 7474);
  $queryString = "match (n) return n limit 10";
  $query = new Everyman\Neo4j\Cypher\Query($client,$queryString);
  #print_r($query->getResultSet());
}*/
?>
