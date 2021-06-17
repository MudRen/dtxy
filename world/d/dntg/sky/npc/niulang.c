//change.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_zhinv();
void create()
{
           set_name(HIG"牛郎"NOR, ({"niu lang", "niulang", "lang"}));
       set("long",
"原来是个放牛娃，后与织女相爱，生下一双儿女，后被罚银河永隔，\n只有每年的七月初七才能鹊桥相会。\n");
         set("gender", "男性");
       set("age", 20);
       set("class", "xian");
        set("title", "");
       set("attitude", "friendly");
       set("per", 30);
	set("int", 30);
           set("max_kee", 1000);
           set("max_gin", 1000);
           set("max_sen", 1000);
           set("force", 1000);
          set("max_force", 1000);
        set("force_factor", 50);
          set("max_mana", 500);
          set("mana", 500);
           set("mana_factor", 0);
          set("combat_exp", 600000);
     set("daoxing", 500000);


          set_skill("literate", 50);
          set_skill("unarmed", 150);
        set_skill("dodge", 100);
          set_skill("force", 100);
          set_skill("parry", 100);
            set_skill("blade", 170);
            set_skill("xuanhu-blade", 170);
          set_skill("spells", 50);
           set_skill("moonshentong", 50);
             set_skill("baihua-zhang", 50);
             set_skill("moondance", 50);
           set_skill("moonforce", 100);
         map_skill("spells", "moonshentong");
         map_skill("force", "moonforce");
             map_skill("blade", "xuanhu-blade");
             map_skill("parry", "xuanhu-blade");
              map_skill("unarmed", "baihua-zhang");
              map_skill("dodge", "moondance");
set("inquiry",([
      "渡河": (: ask_zhinv :),
      ]));
create_family("月宫", 2, "弟子");
setup();

              carry_object("/d/obj/cloth/linen")->wear();
        carry_object("/d/obj/weapon/blade/yuandao")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="男性")){
           command("shake");
             command("say 男女有别，若收了你，日后练功多有不便，你还是另择他人吧!\n");
            return;
}
        command("pat "+ob->query("id"));
        command("say 同是天涯沦落人，今天我就收下你！日后好生练功，他日必有所成！\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}

int accept_object(object me,object ob)
{
       	object book;
       	if( me->query_temp("jueqing/xiwangmu") == 1 && ob->query("from") == "zhinu" )
       	{
       		message_vision ("牛郎专心的读起信来。\n",me);	
       		command ("say 多谢你了，我已经好久没有她的消息了！虽是无奈，可这隔河相望的日子，实在难熬。");
       		command ("say 我这里也有一封信，你帮我带给她吧！");
       		book = new("/d/moon/obj/letter.c");
		book->set("from","niulang");
		book->move(me);
		message_vision("\n牛郎递给你一封信。\n",me);
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
string ask_zhinv()
{
	object book;
	object me=this_player();
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( me->query_temp("jueqing/niulang") )
        {
        	me->delete_temp("jueqing/niulang");
        	me->set_temp("jueqing/zhinv",2);
        	message_vision(HIC"$N说道：时机已到，请牛郎随我渡河与织女相会！\n",me);	
        	command("ah");
        	command("jump");
        	message_vision(HIC"$N架起彩云，带着牛郎来到了西天门！\n",me);	
        	me->move("/d/dntg/sky/xitian");
        	this_object()->move("/d/dntg/sky/xitian");
        	message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗西王母(xi wangmu)：" + me->name() + "玉成牛郎织女，功德无量！\n\n\n"NOR,users());
		return("织女，想死我了。。。");
        }
	return ("我好想她啊！");
}