//zhangsun wuji

inherit NPC;
#include <ansi.h>
#include <quest.h>

void create()
{
	set_name("�����޼�", ({"zhangsun wuji", "wuji"}));
	set("title", "��������");
	set("age", 50);
	set("per", 28);

	set("quest_type", "captor");
        set("inquiry", ([
		"����" : (: give_quest :),
		"gongwen" : (: give_quest :),
	]));	

	setup();
	carry_object("/d/gao/obj/changpao")->wear();
}