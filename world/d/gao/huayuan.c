// huayuan.c

inherit ROOM;

void create()
{
  set ("short", "��԰");
  set ("long", @LONG

��԰�л������࣬ʲô���ɡ����ڡ�������ٺϡ�Ǿޱ��ĵ����
�ȣ�����ö�٣���Ŀ���ǣ�������֮ʱ����԰�к�����ϣ�����
������������һ�ᣬ�úÿ�����
LONG);
set("item_desc",(["flower":
"Ư���Ļ�԰���˲ȵ����߰��㣬�ۼ�һֱͨ����ǽ�ߣ�����\n"
]));

set("exits", ([ /* sizeof() == 4 */
"south" : __DIR__"houyuan",
]));
	set("outdoors", 1);
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}
int do_climb(string arg)
{       object me;
	object who;
        me=this_player();
	who = me->query_temp("ridee");
        if ( !arg || ((arg != "wall") ))
                return notify_fail("��Ҫ��ʲô��\n");
        else
        {
                message_vision("$Nһ��ǽͷ�����˹�ȥ��\n", me);
                //me->set_temp("apply/dodge",0);
                if( who && environment(who) == environment(me) )
                {
                	who->set_temp("no_return",0);
  			who->set_temp("rider",0);
  			me->set_temp("ridee",0);          
  			me->add_temp("apply/dodge",-me->query_temp("ride/dodge"));
  			me->set_temp("ride/dodge",0);
  		}
  		me->move("/d/gao/xiaolu");
		tell_room( environment(me), "�����ˡ�һ����" + me->name() + "��ǽͷ������������\n",
({me}) );
                return 1;
         }
}

