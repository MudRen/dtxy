// ����
// by lestat 2001

inherit ROOM;

void create()
{
        set("short", "��ⶴ");
        set("long", @LONG
������ˮ�����ľ�ͷ�����ܳ�ʪ�����������Ĵ���ʱ��ˮ������һ����ʯ(stone)�ϣ�
��Զ����һ������ʯ����ֻ��һ���ϸ�����ϥ������
LONG );
	set ("item_desc", ([
		"stone" : "�����ʯ�⻬ƽ���������������ס����(push)һ�¡�\n"
	])  ) ;
	set("exits", ([ /* sizeof() == 2 */
		"east" : __DIR__"gudi",
	]));
	set("objects",([
		__DIR__"npc/shengmu" : 1,
	]));
	set("no_clean_up", 0);
	setup();
}

void init()
{
	add_action("do_push","push");
	add_action("do_zuan",({"zuan","enter"}));
}

int do_push(string arg)
{
	object me;
	me = this_player();
//        if((!me->query("family") || (me->query("family/family_name")!="��˿��")) && present("shengmu",environment(me))) 
//             return notify_fail("����ʥĸ˫Ŀ΢�ţ�����˵�������������ˣ�������Σ���\n");
	if (!arg||arg!="stone") return 0;
	write("������˫�ۣ�˫�ַ���һ����ʯ�����һ������������\n");
       if(random((int)me->query("kar")) < 10 )
		{
                write("��ʯ�ζ���һ�£�����һ�μ��ء�\n");
		return 1;
		};
	write("��ʯ����ת����ֻת��һ�룬�����ʯ��¶��һ���������ߵĶ�Ѩ(hole)��\n");
	set("exits/north", __DIR__"yandong");
	return 1;
}

int do_zuan(string arg)
{
	object me;
	me = this_player();
	if (!me->query_temp("marks/push")) return 0;
	if ( arg != "hole") return 0;
	message_vision("$N��ϲ֮�£�Ҳûȥ���Ƕ�������Σ�գ���һ���������ɽ���\n", me);
	me->move(__DIR__"yandong");
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("marks/push") ) me->delete_temp("marks/push");
	return ::valid_leave();
}
