//Cracked by Roath
//huludi.c
#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "���ϵ�");
	set ("long", @LONG

��ׯ�����µĶ࣬�Է���Ҳ���٣����Թ��ڹ��˸�����һЩũ��
�����߲˹Ϲ������������ϵء���������һ��������ɵ���ʣ�
����Ͽ���һ����ª����ľ�ţ����Ϲ���һ�ѻ�ͭ����
LONG);

	set("exits", 
	([ //sizeof() == 4
		"southeast" : __DIR__"baicaidi",
		"southwest" : __DIR__"huludi",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		"/d/obj/food/watermelon" : 3,
	]));

	//create_door("north", "��ľ��", "south", DOOR_CLOSED);
	set("outdoors", "wuzhuang");

	setup();
}

void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{
	object me, key, nroom;

	me = this_player();

	if( !arg || arg != "door" ) 
		return notify_fail("��Ҫ��ʲô��\n");

//    if( !(key = present("huangtong key", me) && key->query("id")=="huangtong key") ) 
  key=present("huangtong key",me);
  if (!key || key->query("id")!="huangtong key")
		return notify_fail("��û�п�����ŵ�Կ�ס�\n");

	//now we are ready to open...

      if( !(nroom = find_object(__DIR__"renshenguo-yuan")) )
                nroom = load_object(__DIR__"renshenguo-yuan");

        if( nroom = find_object(__DIR__"renshenguo-yuan") ) 
        {
                set("exits/north", __DIR__"renshenguo-yuan");
                message_vision("$N�ѻ�ͭԿ�ײ���������š�˰��죬���ڰ�������,��ľ�ſ��ˡ�\n", me);
                nroom->set("exits/south", __DIR__"xiguadi");
		me->set_temp("used_huangtong_key", 1);
		destruct(key);
                call_out("close_door", 600);
	}
	return 1;
	
}

void close_door()
{
        object nroom;

        message("vision", "һ��С��ʿ�ɿ���ܹ���,�����������ˡ�\n", this_object() );
        if( nroom = find_object(__DIR__"renshenguo-yuan")) {
        message("vision", "һ��С��ʿ�ɿ���ܹ���,�����������ˡ�\n", nroom);
        nroom->delete("exits/south");
        }

        delete("exits/north");
}
