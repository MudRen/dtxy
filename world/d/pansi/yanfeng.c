// �ٲ���
// by lestat 2001

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", HIC"�ٲ���"NOR);
	set("long", @LONG
����ǰһ����ԭ�������ٲ��ڱ��ж��죬����Ĵ��ٲ����������գ�������
�£�����һ��ˮ�����ڶ��ڣ����ߺ����������������ڶ���
LONG );
	set("exits", ([
		"north" : __DIR__"gudi",
	]));
	set("no_clean_up", 0);
	setup();
}
void init()
{
	add_action("do_jump","jump");
}
int do_jump(string arg)
{
        object ob;
        int new_sen;
        ob = this_player();
        new_sen = random( ob->query("max_sen")*3 );
        if ( new_sen > ob->query("sen") ) new_sen = ob->query("sen") + 1;
        if( !arg || arg=="" ) return 0;
        if( arg != "down" )
                return notify_fail("��Ҫ����������\n");
        tell_object(ob, HIR"���۾�һ�գ�����һԾ����ˮ����ȥ��������\n"NOR);
        message("vision", NOR"ֻ��" + ob->query("name") + "�۾�һ�գ�������ˮ����ȥ��������\n"NOR, environment(ob), ob);
        if((ob->query_skill("dodge",1)<30)){ ob->unconcious();
        ob->receive_damage("sen",new_sen);
        ob->move(__DIR__"yanfeng");
		}else{
           ob->move(__DIR__"pubu");
        }
        return 1;
}
