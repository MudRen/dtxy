#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("ץ���", ({"ghost seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ�Ż����˷�����ҷ�ֽ��\n");
        set("unit", "��");
        set("value", 0);
	set("no_put",1);
	set("no_sell",1);
	}
	set("special_effects", "none");  // emotion
	setup();
}

string long()
{
	if(query("finished"))
		return "һ������ظ���˼���������ҷ�ֽ��\n"+
		"�Ѿ���һֻ���������ס�ˡ�\n";
	if(stringp(query("desc")))
		return "һ������ظ���˼���������ҷ�ֽ������(burn)��ץ��\n"+
		"ֻ�����滭�ţ�\n"+
		query("desc");
}

void init()
{
	add_action("do_burn", "burn");
}

int do_burn(string arg)
{
	object room, me;
	string name;
	
	if(!arg||!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
	me=this_player();
	
	if(query("finished"))
		return notify_fail("�����Ѿ���һֻ���ˣ����ȥ������ظ�ɡ�\n");
	if(!query("master")||query("master")!=me)
	{
		message_vision(RED"$N��һ������ħ��ֿ���������һ�ӣ�������һ��ץ���������\n\n"NOR, me);
		message_vision("���ʲô��û�з�����\n", me);
		destruct(this_object());
		return 1;
	}
	
	room=environment(me);
	message_vision(RED"$N��һ������ħ��ֿ���������һ�ӣ�������һ��ץ���������\n\n"NOR, me);
	if(file_name(room)+".c"!=query("file_name"))
	{
		message_vision("���ʲô��û�з�����\n", me);
		destruct(this_object());
		return 1;
	}
	name=({ "��ͷ", "����", "����", "�췢"})[random(4)];

	message_vision(HIB"ֻ��һ������������"+name+"���Ѿ���ץ�������ס��\n"NOR, me);
	set("finished", 1);
	return 1;
}
