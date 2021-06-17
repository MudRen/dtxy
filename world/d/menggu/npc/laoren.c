
inherit NPC;
#include <ansi.h>
int ask_long();

void create()
{
       set_name("老牧人", ({"lao muren","muren","lao"}));
       set("title",HIW"草原"NOR);
       set("gender", "男性");
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
          	"忘忧园": (: ask_long :),
          	"巨龙园": (: ask_long :),
          	"巨龙": (: ask_long :),
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
	message_vision("$N对$n说道：咳......咳......人老了，咳......咳......都忘了。\n"NOR,this_object(),who);
	message_vision("$N对$n说道：哎......我的牧马鞭丢了。\n"NOR,this_object(),who);
	return 1;
}
int accept_object(object who, object ob)
{
        if (ob->query("id") == "muma bian" && ob->query("name") == "老人的牧马鞭" && !ob->is_character()) 
	{
		message_vision("$N用一种恐惧的眼神望着$n。\n"NOR,this_object(),who);
		message_vision("$N对$n说道：巨龙......咳......很久前的事。\n"NOR,this_object(),who);
		message_vision("$N说道：风雪夫妇死的好惨。\n"NOR,this_object(),who);
		message_vision("$N说道：很多人都去救他们，结果没有人活着回来。\n"NOR,this_object(),who);
		message_vision("$N说道：他们都是从东北边的悬崖上跳下去找龙的。\n"NOR,this_object(),who);
		command("sigh");
    		who->set_temp("julong_ask",1);
    		who->save();
		return 1;
	}
	return 0;
}

