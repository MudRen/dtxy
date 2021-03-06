//Cracked by Roath

//baihua xianzi
inherit NPC;
inherit F_MASTER;
string ask_jueqing();
string ask_mojie();
void create()
{
       set_name("百花仙子", ({"baihua xianzi", "baihua", "xianzi"}));
       set("long",@LONG
西王母的弟子。奉王母之命，总司天下名花，乃群芳之主。
因与嫦娥不睦，遭其陷害，被谪凡尘。厄满后独居蓬莱，不
与广寒宫来往，所制“百花酿”为天上人间，第一玉液。
LONG);

       set("title", "群芳之主");
       set("gender", "女性");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 30);
        set("int", 30);
       set("max_gin", 600);
  set("max_sen",3000);
  set("max_kee",3000);
   set("force",2000);
       set("max_force", 2000);
       set("force_factor", 100);
       set("max_mana", 2000);
       set("mana", 2000);
       set("mana_factor", 200);
       set("combat_exp", 800000);
       set("daoxing", 1200000);


   set("inquiry",([
   	"百花酿":"可惜这里僻处海外，奇花品种不全。如能在酒中加入(add)它种鲜花，此酒才算酿成。",
   	"绝情": (: ask_jueqing :),
   	"魔界": (: ask_mojie :),
   	]));
        set("eff_dx", 200000);
        set("nkgain", 350);

       set_skill("literate", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 70);
       set_skill("force", 80);
       set_skill("parry", 80);
       set_skill("spells", 80);
       set_skill("moonshentong", 80);
       set_skill("baihua-zhang", 200);
       set_skill("moonforce", 80);
       set_skill("moondance", 70);
       set_skill("whip",80);
       set_skill("jueqingbian",80);
       map_skill("spells", "moonshentong");
       map_skill("unarmed", "baihua-zhang");
       map_skill("force", "moonforce");
       map_skill("dodge", "moondance");

           set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "arrow" :),
               (: cast_spell,"mihun" :),
               (: cast_spell,"shiyue" :),
        }) );
       create_family("月宫", 2, "弟子");
       setup();

       carry_object("/d/moon/obj/luoyi")->wear();
     carry_object("/d/obj/book/makeupbook");
      carry_object("/d/shendian/babu/obj/xiangjing");
       if (clonep()) carry_object("/d/obj/flower/rose")->wear();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
           command("say 我们月宫只收女徒，这位" +
RANK_D->query_respect(ob) + "还是另请高就吧。\n");
           return;}
        if ( !ob->query_temp("denied_by_chang_e")){
          command("shake");
        command("say 我只收有缘之人，这位" +
RANK_D->query_respect(ob) + "还是去请教嫦娥吧。\n");
        return;
}

        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}
string ask_jueqing()
{
	object me=this_player();
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( me->query("betray/count") )
		return ("你三心二意无法领会月宫绝学。\n");
        if( (string)me->query("gender") !="女性")
                return ("你非为纯阴之身,怎能知哓女儿家的心思??\n");
        if(me->query("jueqing_known"))
      		return ("绝情中百花掌的口诀你都已经知道了啊！");
      	if(me->query("jueqing_cant"))
      		return ("你与绝情无缘！");
      	if(me->query("jueqing/baihua"))
      		return ("绝情中百花掌的口诀你都已经知道了啊！");
      	if( !me->query_temp("jueqing/baihua") )
      	{
      		me->set_temp("jueqing/baihua",1);
      		command("sigh");
	      	command("say 问世间情为何物？直叫人生死相许！");
	      	return("我在这蓬莱住了这么多年，只为寻找七叶琼芝草，完成百花酿。你既然有心，就帮我寻来七叶琼芝草，并加入(add)百花酿中！");
	}
	else if( me->query_temp("jueqing/baihua") == 2 )
	{
		return("哇，百花酿终于完成了，嫦娥师妹这下可以好很多了，你这就帮我送去吧，记得快去快回！");
	}
	else if( me->query_temp("jueqing/baihua") == 3 )
	{
		me->delete_temp("jueqing/baihua");
		me->set("jueqing/baihua",1);
		return("师妹身体好多了吧，这就是百花掌的口诀，你记住了！");
	}
      	else
      	{
      		return("快去寻找七叶琼芝草吧！");
      	}
}

string ask_mojie()
{
	object me=this_player();
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( me->query("betray/count") )
		return ("你三心二意无法领会月宫绝学。\n");
        if( (string)me->query("gender") !="女性")
                return ("你非为纯阴之身,怎能知哓女儿家的心思??\n");
      	if(me->query("jueqing_cant"))
      		return ("你与绝情无缘！");
      	if( !me->query_temp("jueqing/binghun") )
      		return ("时机未到！");
      	if( me->query_temp("jueqing/binghun") == 1 )
      	{
      		me->set_temp("jueqing/binghun",2);
	      	command("say 既然你有如此本领，那就去魔界取回冰魂吧。师妹的伤势已经不能再拖下去了！");
	      	command("say 你看这百花谷四季如春，就是因为百花谷地下便是充满岩浆火焰的魔界。");
	      	command("say 不过天下无奇不有，冰魂这天下至寒之物就生在魔界。");
	      	command("say 魔界内的怪物实力非凡、凶恶好斗，所以师傅命织女织造七彩云帛，再辅以百花灵气，封印了魔界通道。");
	      	command("say 如果你此行顺利取得冰魂，魔界必将实力大损，织女也可与牛郎相聚了，可是功德无量啊。");
	      	command("say 至于其他，嫦娥师妹自会告知于你，我这就打开魔界通道。");
	      	return("你从薄命岩跳下（jump down）就可以到达魔界，你取得冰魂以后自会返回！");
	}
	else if( me->query_temp("jueqing/binghun") == 2 )
	{
		return("你从薄命岩跳下（jump down）就可以到达魔界，你取得冰魂以后自会返回。赶紧动身吧！");
	}
	else
	{
		return("赶紧将冰魂送给嫦娥师妹吧！");
	}
}