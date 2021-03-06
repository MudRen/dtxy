// Changed by sjmao  09-11-97
//changed by take 8-12-2001

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
int rank_me();
string expell_me(object me);
string ask_cfpl();

void create()
{
       set_name("龙女", ({"long nu","gongzhu","long","princess"}));

	set("long","紫云宫主人，龙王的女儿．\n");
       set("gender", "女性");
       set("age", 20);
	set("int", 25+random(5));
        set("title", "紫云公主");
       set("attitude", "peaceful");
        set("combat_exp", 350000);
  set("daoxing", 100000);

       set("rank_info/respect", "公主殿下");
       set("class","dragon");
       set("per", 30);
       set("max_kee", 900);
       set("max_sen", 700);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 40);
       set("max_mana", 500);
       set("mana", 400);
       set("mana_factor", 30);
       set_skill("literate", 80);
       set_skill("unarmed", 100);
       set_skill("dodge", 120);
       set_skill("force", 80);
       set_skill("parry", 100);
       set_skill("fork", 80);
       set_skill("spells", 100);
        set_skill("seashentong", 80);
        set_skill("dragonfight", 80);
        set_skill("dragonforce", 80);
        set_skill("fengbo-cha", 100);
        set_skill("dragonstep", 120);
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");

        set("inquiry", ([ "离宫": (: expell_me :),
                "leave": (: expell_me :), 
		"职位": (: rank_me :),
		"叉法": (: ask_cfpl :),
				]) );

    create_family("东海龙宫", 2, "水族");
	setup();

        carry_object("/d/obj/cloth/pinkskirt")->wear();
	carry_object("/d/sea/obj/yincha")->wield();
}
int rank_me()
{
        object me=this_player();
        int exp;
        exp=(int)me->query("combat_exp");
        if( me->query("title") == "东海龙神")
		return notify_fail("你已经是掌门人了，还来要什么职位．\n");
        if( (string)me->query("family/family_name") == "东海龙宫"){
                if( exp <= 100000 ){
                        me->set("title", HIR"东海龙宫"HIY"巡殿虾兵"NOR);
                 } else if(exp <= 1000000 ){
                        me->set("title", HIR"东海龙宫"HIY"巡海夜叉"NOR);
                  } else if(exp < 2000000 ){
                        me->set("title", HIR"东海龙宫"HIY"护宫使"NOR);
                  } else if(exp < 3000000 ){
                        me->set("title", HIR"东海龙宫"HIY"无敌将军"NOR);
                } else {
                        me->set("title", HIR"东海龙宫"HIY"蹈海龙王"NOR);
                }

                tell_object(me, "龙女对你说：你可以做"+me->query("title")+"。\n");
                tell_room(environment(me),
"龙女对"+me->query("name")+"说：你可以做"+me->query("title")+"。\n", ({me, me}));
         CHANNEL_D->do_channel(me,"chat","现授予本门弟子"+me->query("name")+""+me->query("title")+"一职。恭请各位仙长多加捧场！");
     me->save();  
        }
        return 1;
}
void attempt_apprentice(object ob)
{
        command("jump");
	command("say 我又多了一个弟子耶！\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "dragon");
}
string expell_me(object me)
{
  me=this_player();
  if((string)me->query("family/family_name")=="东海龙宫")
    {
      message_vision("紫云公主难过地望着$N，欲言又止。\n", me);
      return ("你去问我父王吧。\n");
    }
  return ("去问问别人吧！我怎么会知道！n");
}

void die()
{
	object me,who,longjin;
    string whoid;
    me=this_object();
    if(me->query_temp("longjin_kill"))
	{
		  whoid=me->query_temp("longjin_kill");
    	  if (!present(whoid,environment()))
        	  return ::die();
	  	  who=present(whoid,environment());
          if((who->query("fangcun/panlong_hell_18")=="done")&&(who->query("fangcun/panlong_hell_longjin")=="begin")&&(environment()))
		{
			  longjin=new("/d/sea/obj/longjin");
			  longjin->move(me);
			  ::die();
			  return; 
		}
	}
      ::die();
}

string ask_cfpl()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会龙宫绝学。\n");
	if(me->query("family/family_name") != "东海龙宫" )
                return ("你不是我龙宫弟子!!\n");
        if(me->query("cfpl_cant"))
      		return ("你的资质不适合学习乘风破浪！");
        if(me->query("cfpl_known")>1)
      		return ("乘风破浪的口诀你都已经知道了啊！");
      	if(me->query("cfpl_lingwu"))
      		return ("快去找妈祖娘娘吧！");
      	if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
                return ("你的叉法级别还不够！\n");
        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
                return ("你的锤法级别还不够！\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
                return ("你的掌法级别还不够！\n");
      	me->set_temp("cfpl/fork",1);
      	command("xixi");
      	return ("风波十二叉的口诀就刻在龙宫至宝九股托天叉之上，你去找军师问问吧！");
}