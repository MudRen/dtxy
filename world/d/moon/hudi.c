//Cracked by Roath
// Room: /moon/ontop.c
//cglaem...12/13/96.

inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

���˺���������ף������������Ⱦ�����������壮
LONG);
  set("exits", ([ /* sizeof() == 3 */
  "up" : __DIR__"lotuspond",
        ]));
  setup();
}
void init()
{
  add_action("do_dig", "dig");
}


int valid_leave(object me, string dir)
{
    	message_vision("$Nƴ�����������ϰ��������������ˮ��\n", me);
	me->set("water", (int)me->max_water_capacity());
	return ::valid_leave(me, dir);
}

int do_dig(string arg)
{
  object me=this_player();
  object m; 
  if( (!arg) || !((arg == "lotusroot") || (arg == "root") || (arg == "ou")))
    return notify_fail("��ʲô��\n");
  else
    {
      message_vision("$N���������������£�ϣ����Ū��ź�ԣ�\n", me);
      if (random(6) < 1)
        {
       		 message_vision("$N�ٰ��٣��ٵ�һ�ô���ź��\n", me);
       		 if( random(5) || me->query_temp("jueqing/chimeng") != 1 )
		 	m = new(__DIR__"obj/ou.c");
		 else
		 {
		 	m = new(__DIR__"obj/tongxinlian.c");
		 	me->set_temp("jueqing/chimeng",2);
		 	message_vision("$N�����ڵ���ͬ����ź���Ͻ�ȥ�ҳ��ΰɣ�\n", me);
		 }
       	   	 m->move(me); 
	}
    }
  me->receive_damage("sen", (int)me->query("max_sen")*10/100);
  return 1;
}