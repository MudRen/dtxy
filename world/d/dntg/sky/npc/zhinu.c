//change.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_niulang();
void create()
{
           set_name(HIM"织女"NOR, ({"zhi nu", "zhinu", "xian"}));
       set("long",
"西王母的外甥女。因为私自下凡与牛郎相爱，而被罚银河永隔，\n只有每年的七月初七才能鹊桥相会。\n");
       set("gender", "女性");
       set("age", 20);
       set("class", "xian");
        set("title", "");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 30);
	set("int", 30);
         set("max_kee", 1500);
         set("max_gin", 1500);
         set("max_sen", 1500);
         set("force", 1200);
         set("max_force", 1200);
       set("force_factor", 50);
         set("max_mana", 1200);
         set("mana", 1200);
         set("mana_factor", 80);
         set("combat_exp", 800000);
    set("daoxing", 2000000);


	set("inquiry",([
      "牛郎": (: ask_niulang :),
      ]));
         set_skill("literate", 140);
         set_skill("unarmed", 120);
       set_skill("dodge", 180);
         set_skill("force", 120);
         set_skill("parry", 120);
           set_skill("blade", 150);
           set_skill("xuanhu-blade", 150);
         set_skill("spells", 120);
          set_skill("moonshentong", 120);
          set_skill("baihua-zhang", 120);
          set_skill("moonforce", 120);
        set_skill("moondance", 200);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
            map_skill("blade", "xuanhu-blade");
            map_skill("parry", "xuanhu-blade");
        map_skill("dodge", "moondance");

create_family("月宫", 2, "弟子");
setup();

             carry_object("/d/moon/obj/luoyi")->wear();
             carry_object("/d/obj/flower/rose")->wear();
       carry_object("/d/obj/weapon/blade/yangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
             command("say 男女有别，若收了你，日后练功多有不便，你还是另择他人吧!\n");
            return;
}
        command("pat "+ob->query("id"));
        command("say 既然你也是痴情女，我就收下你！日后好生练功，他日必有所成！\n");
        command("recruit " + ob->query("id") );
        return;
}
string ask_niulang()
{
	object book;
	object me=this_player();
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( me->query_temp("jueqing/zhinv") == 1 )
        {
        	me->set_temp("jueqing/niulang",1);
        	message_vision(HIC"$N说道：魔界目前实力大损，王母说你和牛郎相会的时机已经到了！\n",me);	
        	command("ah");
        	command("jump");
		return("真是太好了，相隔千年，终能相会，多谢你了，还麻烦你带我夫君渡河前来相会！");
        }
      	if( me->query_temp("jueqing/xiwangmu") != 1)
      		return ("你是何人，来打听我夫君？！");
      	command("sigh");
	command("say 想不到，师父虽然不说，心里还想着我们！");
	book = new("/d/moon/obj/letter.c");
	book->set("from","zhinu");
	book->move(me);
	message_vision("\n织女递给你一封信。\n",me);
	return ("现在时机不到，我还无法见到夫君，你就帮我把这封信送给他吧！");
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}

int accept_object(object me,object ob)
{
       	if( me->query_temp("jueqing/xiwangmu") == 1 && ob->query("from") == "niulang" )
       	{
       		command ("say 多谢你了，你回去告诉师父，我这里一切都好！");
       		command ("say 这是玄狐唱恨刀的口诀，你记住了！");
       		me->set_temp("jueqing/xiwangmu",2);
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	
       	else
       		return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}