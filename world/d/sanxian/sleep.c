inherit ROOM;
#include <ansi.h>
void create()
{
        set("short","С��");
        set("long", @LONG

һ��С�ݣ��ѷ���Щ��ľ��ϸ�ݣ���������ǿ���Դ���
LONG
        );

        set("sleep_room",1);
        set("if_bed",1);

set("objects", ([
      
      
//        __DIR__"jiandao_book":1,
     ]) );  
        set("exits", ([
                "south" : __DIR__"huating",
"west" :  __DIR__"jianzhong",
        ]));

        setup();
}
void init()

{

add_action("do_search", "search");

}

int do_search(string arg)
{
	int kar;
	object book;

	if(!random(10)) set("research",1);
	kar = this_player()->query("kar");
	if( random(kar+20) < kar && query("research")) 
	{
		message_vision("�ڲ�ľ��ϸ����$Nϸϸ������ͻȻ$N������һ��ʲô������\n", this_player());
		message_vision("$N�����������뻳�С�\n", this_player());
		book = new(__DIR__"jiandao_book");
		book->move(this_player());
		if(!this_player()->query("m_success/������ƪ"))
        	{
                	this_player()->set("m_success/������ƪ",1);
                	this_player()->add("potential",200+random(200));
        	}
	}
	set("research",0);
	return notify_fail("���ڲ�ľ��ϸ����ϸϸ������ȴ���ᶼû���֡�\n");

}

/*void reset()

{

if(!random(10)) set("research",1);

}
*/