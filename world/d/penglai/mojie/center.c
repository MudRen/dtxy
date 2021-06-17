// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

inherit ROOM;
void create()
{
        set("short", "ħ������");
        set("long", @LONG
�����������������ȫ�෴��һƬ����ѩ�أ�������θ��ӣ����Ժúõ�������search��һ�¡�
LONG
        );
        set("exits", ([ 
  "out" : __DIR__"zhaoze7",
]));
        set("objects", ([
                __DIR__"npc/dragon" : 1,
       ]) );
        setup();
}

void init()
{
	object mo,ob;
	add_action("do_search", "search");
 	if( interactive( ob = this_player()) )
 	{
 		if( ob->query_temp("jueqing/binghun") == 2 && objectp(mo = present("binghun guard",environment(ob))) )
 		{
 			mo->copy_status(mo,ob,9);
 		}
	}
}

int do_search()
{
	int kar;
	object me = this_player();
	object mo = present("binghun guard",environment(me));
	object binghun;
	if( mo )
	{
		return notify_fail("�����ػ���һ����������ǰ��\n");
	}
	if( me->is_busy() )
	{
		return notify_fail("����æ���ء�\n");
	}
	kar = me->query("kar");
	me->start_busy(3);
	if( random(kar) > 28 ) 
	{
		message_vision("$N��ϸ�����ŵ��ϣ�ͻȻ������һ��ʲô������\n", me);
		message_vision("$N�����������뻳�С�\n", me);
		me->set_temp("jueqing/binghun",3);
		binghun = new(__DIR__"obj/binghun");
		binghun->move(me);
		message_vision("$N������꣬��Χ�����¿�ʼ���ߣ����ϵı�ѩ���Ŀ�ʼ�ڻ��ˡ�\n", me);
		message_vision("$N�ۼ����ܵ����ҿ�ʼ���������д󼱡�\n", me);
		message_vision("ͻȻ�����ϴ���һ�ɾ޴����������$N������ħ�磡\n", me);
		me->move("/d/penglai/bomingyan");
		return 1;
	}
	return notify_fail("����ϸ���˰��죬���ʲô��û���֡�\n");
}
