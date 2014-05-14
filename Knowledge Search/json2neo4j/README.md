把用json描述的数据存入neo4j数据库中
图格式的描述：
  有两种类型的节点：
    1.每个词条名及其infobox属性值分别对应类型为ENTITY的节点
    2.每个词条的每个开放分类对应一个类型为CATEGORY的节点
  节点之间有两种类型的边：
    1.从entity类型的节点连向category类型的节点的CATEGORY类型的边:
      表示一个节点属于某种类型
    2.entity节点之间PROPERTY类型的连接：
      表示infobox的关系，边的name值表示infobox的属性，被指向的节点表示infobox的值

用法：python savehudongjson.py filename.json
