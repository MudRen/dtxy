inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

    ���￴�����Ѿ�����·�����ˣ�ǰ����һ�������
Ͽ�ȡ�
LONG);
set ("outdoors", 1);  set("exits", ([ /* sizeof() == 1 */
  "north" : "/d/moon/yunu1",
]));
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

        if ( !arg || ((arg != "down") ))
                return notify_fail("��Ҫ��������\n");
        else
message_vision("$N̾�˿�������һ�գ�������Ͽ������ȥ������\n",me);

                me->move("/d/kunlun/yaxia");
                message_vision("��ǰһ����ԭ�����ﾹȻ��һ��������Դ��\n", me);
                return 1;
}
