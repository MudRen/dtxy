
inherit NPC;
#include <ansi.h>
int ask_long();

void create()
{
       set_name("������", ({"lao muren","muren","lao"}));
       set("title",HIW"��ԭ"NOR);
       set("gender", "����");
       set("combat_exp", 50000);
       set("age", 25);
       set("per", 24);
       set("str", 100);
       set("force", 400);
       set("max_force", 200);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 200);
       set_skill("dodge", 200);
       set_skill("force", 200);
        set("inquiry", ([
          	"����԰": (: ask_long :),
          	"����԰": (: ask_long :),
          	"����": (: ask_long :),
]));

       setup();
       carry_object("/d/obj/cloth/linen")->wear();
}
void init()
{
    ::init();

}
int ask_long()
{
    	object who=this_player();
    	object ob=this_object();
	message_vision("$N��$n˵������......��......�����ˣ���......��......�����ˡ�\n"NOR,this_object(),who);
	message_vision("$N��$n˵������......�ҵ�����޶��ˡ�\n"NOR,this_object(),who);
	return 1;
}
int accept_object(object who, object ob)
{
        if (ob->query("id") == "muma bian" && ob->query("name") == "���˵������" && !ob->is_character()) 
	{
		message_vision("$N��һ�ֿ־����������$n��\n"NOR,this_object(),who);
		message_vision("$N��$n˵��������......��......�ܾ�ǰ���¡�\n"NOR,this_object(),who);
		message_vision("$N˵������ѩ�����ĺòҡ�\n"NOR,this_object(),who);
		message_vision("$N˵�����ܶ��˶�ȥ�����ǣ����û���˻��Ż�����\n"NOR,this_object(),who);
		message_vision("$N˵�������Ƕ��ǴӶ����ߵ�����������ȥ�����ġ�\n"NOR,this_object(),who);
		command("sigh");
    		who->set_temp("julong_ask",1);
    		who->save();
		return 1;
	}
	return 0;
}

