
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_long();

void create()
{
       set_name("��ѩ", ({"feng xue","feng","xue"}));
       set("title",HIW"��Į��"NOR);
       set("gender", "����");
       set("combat_exp", 5000000);
       set("age", 25);
       set("per", 24);
       set("str", 100);
       set("force", 400);
       set("max_force", 200);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 200);
       set_skill("sword", 250);
       set_skill("wangqing-jue", 410);
       set_skill("dodge", 200);
       set_skill("force", 200);

       setup();
       carry_object("/d/obj/cloth/linen")->wear();
}
void init()
{
    ::init();
}
int recognize_apprentice(object ob, object who)
{
    	if (this_player()->query("mark/jinlong")!="wangqing")
    	 	return notify_fail("��ѩ�ɻ�Ŀ�����������Һ���ʦͽ֮Ե��\n"); 
    	return 1;
}
