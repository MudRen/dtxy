//changan city
// Cracked by �辪ѩ 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "���Ѷ���");
        set ("long", 
"������������ˣ���ǰһƬ�谵����ǰ��ȥ·�����ܶ�\n"
HIG"ʯͷ(stone)"NOR"����ס�ˡ�\n\n"

);
	set("objects", ([ /* sizeof() == 1 */
        	__DIR__"npc/longnu.c" : 1,
	]));
  	set("item_desc", ([ /* sizeof() == 1 */
  		"stone" : HIY"�ܶ�޴��ʯ�飬���������(push)����\n"NOR,
  		"ʯͷ" : HIY"�ܶ�޴��ʯ�飬���������(push)����\n"NOR
	]));
        setup();
}
void init()
{
	add_action("do_push","push");
add_action("do_cast",({"cast"}));
}

int do_push(string arg)
{
	int i;
	object *inv;
        object ob ,room;
        ob = this_player();
        if(!( room = find_object("/d/menggu/longjiao")) )
                room = load_object("/d/menggu/longjiao");
        if( !arg || arg=="" ) return 0;
        if( ob->query_temp("julong_ask")!=1 ) return 0;
	if ( present("julong nu") )
		return notify_fail("��ū������ס���㡣\n");
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
                	{message("vision", NOR"�����ϱ���ʲô��������ò�Ҫ����������Σ�յġ�\n"NOR,ob);
			return 1;}
                }
        if( arg != "stone" && arg != "ʯͷ")
                return notify_fail("��Ҫ��ʲô��\n");
        tell_object(ob, HIG"���þ��������������ǰ��ʯͷ�ƿ���һЩ��������\n"NOR);
	if (room->query("push") == "south")
        	{
        	tell_object(ob, HIR"��Ѿ�����������������ѡ�\n"NOR);
        	ob->move("/d/menggu/longjiao");
                ob->set_temp("julong_kill",1);
                 room->add("hero",1);
        	return 1;
        	}
	if (room->query("push_id") == (string)ob->query("id"))
        	return 1;
	if (room->query("push") == "east")
        	return 1;
	if (room->query("push") == "north")
	{
	room->set("push","east");
	room->set("push_id",ob->query("id"));
        return 1;
	}
        return 1;
}

int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;
    if(member_array(arg,banned_cast)==-1) return 0;
    write("����ط�û��ʹ��"+arg+"��\n");
    return 1;
}

