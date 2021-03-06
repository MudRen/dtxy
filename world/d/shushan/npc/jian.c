// tomcat
// 

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int begin_go();
string ask_sword();
void create()
{
        set_name("白眉", ({ "bai mei", "bai", "mei" }));
        set("title",HIW"蜀山祖师"NOR);
        set("long", "这位满头白发的老人，一双银白的长眉低垂。\n");

        set("gender", "男性");
        set("age", 120);
        set("attitude", "peaceful");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("per", 40);
        set("class","swordsman");
        
        set("kee", 8000);
        set("max_kee", 8000);
        set("sen", 8000);
        set("max_sen", 8000);
        set("force", 12000);
        set("max_force", 6000);
        set("max_mana",6000);
        set("mana",12000);
        set("force_factor", 400);
        set("mana_factor", 400);
        set("combat_exp", 10000000);
        set("daoxing", 10000000);

        set_skill("spells",300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("zixia-shengong", 300);
        set_skill("sevensteps", 300);
        set_skill("hunyuan-zhang", 300);
        set_skill("literate", 300);
        set_skill("unarmed", 300);
        set_skill("mindsword", 300);
        set_skill("yujianshu", 300);
        set_skill("taoism",300);
        map_skill("spells", "taoism");
        map_skill("dodge", "sevensteps");
        map_skill("force", "zixia-shengong");
        map_skill("parry", "mindsword");
        map_skill("sword", "yujianshu");
        map_skill("unarmed", "hunyuan-zhang");


 create_family("蜀山派", 1, "祖师");
	set("sword_known",8);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed","fenguang" :),
                (: perform_action, "sword","wanjian" :),
                (: perform_action, "sword","sword" :),
                (: perform_action, "sword","duanshui" :),
                (: perform_action, "sword","fumo" :),
                (: cast_spell, "chaoyuan" :),                
        }) );
       set("inquiry", ([
                "灵台观礼"    : (: begin_go :),
                "剑心"    : (: ask_sword :),
       ]) );
        setup();
        
        carry_object("/d/obj/cloth/jinpao")->wear();
        carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}
void attempt_apprentice(object ob)
{        
        if (ob->query_skill("yujianshu",1) < 180) {
        command("say 我蜀山派，最注重御剑术的修行，依我看" + RANK_D->query_respect(ob) + "是不是该多下下苦功呢？");
                return ;
        }
        
        if ((int)ob->query("daoxing") < 1000000 ) {
  	command("say 你道行太低了。\n");
	return;
	}

        if (ob->query("obstacle/number") < 26) {
	command("say 这位" + RANK_D->query_respect(ob) + "拜我为师，要先先历尽取经劫难！\n");
	command("sigh");
	return;
	}        
        command("say 好吧，我就收下你了。");
        command("recruit " + ob->query("id"));
        ob->set("class", "swordsman");
        ob->set("title",HIC"独孤求败"NOR);
}

int begin_go()
{
  object me,ob;
 int dx,dx1,wx,qn;
 me=this_player();
 ob=this_object();
 dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
 dx1=dx/1000;
 wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
 qn=30000;
 if (!me->query("fangcun/panlong_visite"))
 return 0;
 if (me->query("guanli/shushan"))
  return 0;
          if (me->query("fangcun/panlong_shushan")=="done")
{
     message_vision("\n白眉哈哈大笑道：好,好,老朽就走这一趟！\n"NOR,me);
      message_vision(HIY"\n话音刚落白眉就不见了！\n"NOR,me);
        ob->move("/d/lingtai/inside1");
    me->move("/d/lingtai/inside1");
      return 1;
}
if ((me->query_temp("fangcun/panlong_shushan_jiansheng")=="done")&&(me->query_temp("fangcun/panlong_shushan_jiujianxian")=="done")&&(me->query_temp("fangcun/panlong_shushan_lixiaoyao")=="done"))
{
   me->add("fangcun/panlong_visite",1);
   me->set("fangcun/panlong_shushan","done");
     message("chat",HIC+"〖"+HIW+"大唐西游"+HIC+"〗白眉(Bai mei)："+me->query("name")+"收齐我徒儿徒孙信物,届时蜀山派一定前来灵台观礼！\n"NOR,users());
  message("chat",HIC+"〖"+HIW+"大唐西游"+HIC+"〗白眉(Bai mei)："+me->query("name")+"得到奖励：道行"+chinese_number(dx1)+"年，武学"+wx+"点，潜能30000点．\n"NOR,users());
    if (me->query("family/family_name")=="方寸山三星洞")
            message_vision("\n白眉道：届时烦请" + RANK_D->query_respect(me) + "再来通知老朽一声.\n"NOR,me);
   me->add("daoxing",dx);
   me->add("combat_exp",wx);
  me->add("potential",30000);
 if ((me->query("family/family_name")!="方寸山三星洞")||(me->query("fangcun/panlong_noway")))
    me->set("guanli/shushan",1);
 return 1;
}
 if (me->query_temp("fangcun/panlong_shushan_laozu")=="begin")
{
      message_vision("\n白眉道：三件东西都拿到了吗？\n"NOR,me);
     return 1;
}
 if (me->query_temp("fangcun/panlong_shushan_jiansheng")=="begin")
{
message_vision("\n白眉睁开眼睛上上下下打量了一遍$N,然后缓缓说道.\n\n"NOR,me);
        call_out("begin_go1",3);
        return 1;
}
 command("shake " + me->query("id"));
  return 1;
}

int begin_go1()
{
 object me;
 me=this_player();
 command("say 自那猴子后,方寸山一直没出现过人才,如今你能悟出千均棒精要招
               来天龙,当真是菩提老道之福啊！既然是老道士派人来请，我就走这
        一趟，不过你先要拿到我两个徒儿和我那逍遥徒孙的信物．");
me->set_temp("fangcun/panlong_shushan_laozu","begin");
}

int accept_object(object me, object ob)
{
 string myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
 if ((me->query_temp("fangcun/panlong_shushan_jiansheng") == "begin")||(me->query_temp("fangcun/panlong_shushan_jiansheng") == "done"))
{
   if ((string)ob->query("id") == "jiansheng xinwu")
{
 command ("nod");
 command ("say 没错,是我大徒弟的东西！");
 me->set_temp("fangcun/panlong_shushan_jiansheng","done");
 return 1;
}
if (ob->query("id") == "jiujianxian xinwu")
{
command ("haha");
 command ("say 不错,是我二徒弟身上的那股酒味！");
me->set_temp("fangcun/panlong_shushan_jiujianxian","done");
 return 1;
}
if (ob->query("id") == "lixiaoyao xinwu")
{
command ("sigh");
command ("say 不见我那小徒孙已有些时日了！");
 me->set_temp("fangcun/panlong_shushan_lixiaoyao","done");
return 1;
}
 else
{
command ("say 这是什么？");
 return 1;
}
}
 else
{
 command ("say 大胆狂徒,敢来蜀山捣乱？ ");
 message_vision("\n\n白眉袍袖一摆,$N顿时如坠入了云雾中.也不知道被吹到了哪里？\n\n"NOR,me);
 me->move("/d/city/kezhan");
 return 0;
}
}
void destroy(object ob)
{
 destruct(ob);
return;
}
void dropthing(string thing)
{
 command("drop "+thing);
return;
}
string ask_sword()
{
	object me = this_player();
	object weapon,jianling,user;
	if( me->query("betray/count") )
		return ("你三心二意无法领会蜀山绝学。\n");
	if(me->query("family/family_name") != "蜀山派" )
                return ("你不是我蜀山弟子!!\n");
        if(me->query("sword_cant"))
      		return ("你无法领悟更高的剑心！");
        if(me->query("sword_known") > 7 )
      		return ("剑心的口诀你都已经知道了啊！");
      	if( me->query_skill("literate",1) < 200 )
		return ("你这点学识不足以领悟剑心！");
	if( me->query_skill("yujianshu",1) < 200 )
		return ("你这点剑法不足以领悟剑心！");
	if( me->query_skill("zixia-shengong",1) < 200 )
		return ("你这点内功不足以领悟剑心！");	
    	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)(weapon->query("skill_type")) != "sword")
	{
		return ("你没有带剑，怎么领悟剑心？ :)\n");
	}
      	command("smile");
	command("say 好，竟然已经体会到了剑心，我蜀山后继有人了！");
	jianling = present("jian ling",load_object("/d/shushan/shengdi/sword_room"));
	if( jianling )
	{
		user = present(jianling->query("owner"),load_object("/d/shushan/shengdi/sword_room"));
		if( user )
			return ("圣地中正有人参悟，你还是等等吧！");
		else
			destruct(jianling);
	}
	command("say 我蜀山派数代经营，开辟出一处圣地，里面藏有各代大家的修炼心得，我这就送你一程，你好好参悟，莫要辜负前辈的一片苦心！");
	message_vision("\n\n白眉袍袖一摆,$N顿时如坠入了云雾中.也不知道被吹到了哪里？\n\n"NOR,me);
 	me->move("/d/shushan/shengdi/kongdi");
	return ("我蜀山果然人才济济！");
}