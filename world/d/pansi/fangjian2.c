// �һ��� ����ʮ������
// by lestat
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM"�һ���"NOR);
        set("long", 
"�����һ����ӵ��Է������ڹ���"+HIM"֩����"NOR+"��������ճ�Ų���"+HIM"�һ�"NOR+"�����������
���˱ǣ�ż����һ��Ƭ"+HIM"�һ�"NOR+"��������Ʈ�䣬ɷ�Ǻÿ���\n"
             );
       set("exits", ([
               "south" : __DIR__"shiji2",
       ]));

	    set("objects",([
		__DIR__"npc/niang" : 1,
	]));
	
       set("no_clean_up", 0);
       setup();
}

void init()
{
        add_action("do_han", "han");
}

int do_han(string arg)
{
	object me;
	me = this_player();

	if( !arg || arg=="" ) return 0;

	if( arg=="֥�鿪��") 
	{
		tell_object(me,"�����ǽ�ڴ��һ������֥�鿪�ţ���\n");
		message("vision", "����һ�������ֻ����һ���¡¡��������������һ�����š�\n", me);
		set("exits/down", __DIR__"shishi4");
		remove_call_out("close");
		call_out("close", 5, this_object());
		return 1;
	}
}

void close(object room)
{
	message("vision","һ���¡¡����������ʯ���ֻ����ع����ˡ�\n", room);
	room->delete("exits/down");
}
int valid_leave(object me,string dir)
{
        if(dir=="down" && (!me->query("family") || (me->query("family/family_name")!="��˿��")) && present("niang",environment(me))) 
             return notify_fail("����ʮ��һ��������ס�����ȥ·��\n");
        return ::valid_leave(me,dir);
}
