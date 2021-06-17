//sgzl
inherit ROOM;

void create ()
{
	set ("short", "雪岭");
	set ("long", @LONG

茫茫的山坡上一望无际的白雪，上面落着几对浅浅的足迹，显然能
攀援到这一层的雪山弟子，轻功几然十分了得了。
翻(jump)过前面的石壁(shi bi)就可到达雪山的顶峰了。
LONG);


	set("exits", 
	([ //sizeof() == 4
                "down" : __DIR__"xuejie-3",
                "west" : __DIR__"no4-w1",
                "east" : __DIR__"no4-e",
"up" : __DIR__"lingjiudong",
	]));
	set("objects", 
	([
                __DIR__"npc/chongzi" : 2,
	]));


	set("outdoors", "xueshan");

	setup();
}

void init()
{
        add_action("do_jump", "jump");
}


int do_jump(string arg)
{       
        object me;
        me=this_player();

        if ( !arg || ((arg != "shi bi") ))
                return notify_fail("你要往哪跳？\n");
        else if(me->query("kee")<50)   
          {
           message_vision("$N脚下一划，身不由自主的向後摔去。\n",me);
           me->unconcious();
          }
        else if((int)me->query_skill("dodge", 1)<300)   
          {
           message_vision("$N奋力向上一纵，结果离地不到三尺就一头摔了下来。\n",me);
           me->add("kee",-20); 
          }
	else
          {
           me->add("kee",-50); 
           message_vision("$N纵身一跃，轻巧的翻过石壁。\n",me);
           me->move("/d/xueshan/shanding");
           tell_room(environment(me),"只见"+me->name()+"飞身跃了上来。\n", me);
           return 1;
           }
        return 1;
}
