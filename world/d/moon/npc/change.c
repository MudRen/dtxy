//change.c
inherit NPC;
inherit F_MASTER;
string ask_jueqing();
void destroy(object ob);
void create()
{
       set_name("嫦娥", ({"chang e", "change", "chang","master"}));
       set("long",
"西王母的大弟子。早年因帮助丈夫盗取西王母之灵药而\n与其师势成水火。后得和解并邀西王母出掌月宫一门。\n");
       set("title", "月宫主人");
       set("gender", "女性");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 30);
	set("int", 30);
       set("max_kee", 900);
       set("max_gin", 600);
       set("max_sen", 800);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 600);
       set("mana", 600);
       set("mana_factor", 40);
       set("combat_exp", 400000);
  set("daoxing", 800000);


        set("eff_dx", 200000);
        set("nkgain", 350);
	set("inquiry",([
      "绝情": (: ask_jueqing :),
      ]));
       set_skill("literate", 80);
       set_skill("unarmed", 80);
       set_skill("dodge", 180);
       set_skill("force", 80);
       set_skill("parry", 80);
       set_skill("sword", 80);
       set_skill("spells", 80);
        set_skill("moonshentong", 80);
        set_skill("baihua-zhang", 80);
        set_skill("moonforce", 80);
        set_skill("snowsword", 80);
        set_skill("moondance", 200);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");

create_family("月宫", 2, "弟子");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/moon/obj/feijian")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="女性")){
           command("shake");
           command("say 我们月宫只收女徒，这位" +
RANK_D->query_respect(ob) + "还是另请高就吧。\n");
           return;}
        if ( (int)ob->query("per") <22){
	  command("shake");
	command("say 以我看这位" +
RANK_D->query_respect(ob) + "的资质并不适于跳舞，还是另请高就吧。\n");
  ob->set_temp("denied_by_chang_e",1);
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
int accept_object(object me,object ob)
{
       	if( me->query_temp("jueqing/chimeng") == 2 && ob->query("id") == "tongxin lianou" )
       	{
       		command ("say 多谢你了，你快去找痴梦师姐吧。祝你早日领悟绝情鞭！");
       		me->set_temp("jueqing/chimeng",3);
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/baihua") == 2 && ob->query("baihua") )
       	{
       		command ("say 百花师姐终于完成百花酿了，为了我可是让大家费尽了心思了，你快去找百花师姐吧，别辜负了她一片心意！");
       		me->set_temp("jueqing/baihua",3);
       		me->set("leaf",ob->query("baihua"));
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/binghun") == 3 && ob->query("id") == "bing hun" )
       	{
       		command ("say 这么多年了，终于拿到了冰魄之魂，我的伤势也该好了！");
       		command ("say 只是我已多年不在外间走动，怕是疏懒的习惯了，还请你再帮我一个忙！");
       		command ("say 请你帮我寻找一个人，按照师傅推算，此人今生应转世为荆棘岭的一个猎户！");
       		command ("say 此人天生对弓箭敏感，听说将军府的乾坤弓、震天箭乃是宝物，你不妨带去一试！");
       		me->set_temp("jueqing/houyi",1);
       		me->set("jueqing/binghun",1);
       		call_out("destroy", 2, ob);
       		return 1;
       	}
       	return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
   }
   
string ask_jueqing()
{
	object book;
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会月宫绝学。\n");
	if(me->query("family/family_name") != "月宫" )
                return ("你不是我月宫弟子!!\n");
        if( (string)me->query("gender") !="女性")
                return ("你非为纯阴之身,怎能知哓女儿家的心思??\n");
        if(me->query("jueqing_cant"))
      		return ("你与绝情无缘！");
        if( me->query("jueqing_known") > 1 )
      		return ("绝情的口诀你都已经知道了啊！");
      	if( !me->query("jueqing_known") )
      	{
	      	if( !me->query("jueqing/chimeng"))
	      		return ("你先去找痴梦师姐吧！");
	      	//if( !me->query("jueqing/zhinu"))
	      	//	return ("你先去找织女师姐吧！");
	      	if( !me->query("jueqing/baihua"))
	      		return ("你先去找百花师姐吧！");
	      	if( !me->query("jueqing/xiwangmu"))
	      		return ("你先去找我师父吧！");
	      	if( present("duanchang book",me) )
	      		return ("书都拿到了，还不好好研读(read book)？！");
	      	command("sigh");
		command("say 难得你如此有心，我就传你绝情四式的口诀，不过能不能领悟还要看你的机缘！");
		//command("say 其实我从来没有练习过绝情四式，只是百般无赖之中每有所悟，自录于薄绢之上，你拿去自己研读一下吧！");
		book = new("/d/moon/obj/duanchang.c");
		if( objectp(book) )
			book->move(me);
		else
			tell_object(me,"哎呀，断肠集不见了，快去找巫师！\n");
		message_vision("\n嫦娥递给$N一本绢书。\n",me);
		return ("其实我从来没有练习过绝情四式，只是百般无赖之中每有所悟，自录于薄绢之上，你拿去自己研读一下吧！");
	}
	else//第二段
	{
		if( me->query_skill("moonforce",1) < 300 
		    || me->query_skill("moonshentong",1) < 300 
		    || me->query_skill("xuanhu-blade",1) < 300 
		    || me->query_skill("jueqingbian",1) < 300 
		    || me->query_skill("snowsword",1) < 300 
		   )
			return ("你修为不够，还不能完全掌握绝情的威力！");
		if( me->query_temp("jueqing/houyi") == 1 ) return ("荆棘岭、乾坤弓、震天箭，你记住了！");
		if( me->query_temp("jueqing/houyi") == 2 ) return ("我想只有九天神箭才能让他恢复记忆了，你去找师傅问一声吧，她应该知道一些情况！");
		if( me->query_temp("jueqing/sun") == 1 ) return ("你快点去找后羿吧！");
		if( me->query_temp("jueqing/sun") == 2 ) return ("太谢谢你了，再麻烦你请后羿前来月宫可以嘛？！");
		if( me->query("jueqing/binghun") && !me->query("jueqing/houyi") )
		{
			command ("say 谢谢你帮我拿到了冰魂！");
       			command ("say 只是我已多年不在外间走动，怕是疏懒的习惯了，还请你再帮我一个忙！");
       			command ("say 请你帮我寻找一个人，按照师傅推算，此人今生应转世为荆棘岭的一个猎户！");
       			command ("say 此人天生对弓箭敏感，听说将军府的乾坤弓、震天箭乃是宝物，你不妨带去一试！");
       			me->set_temp("jueqing/houyi",1);
			return ("我等你的好消息！");
		}
		if( me->query("jueqing/houyi") )
		{
			me->set_temp("jueqing/sun",1);
			return ("你请后羿将你送到九天之上，找太阳神问问关于射日的事情吧！");
		}
		if( !me->query_temp("jueqing/binghun") )
		{
			command("say 看来你对绝情领悟更进了一步，既然如此，我就传你绝情后四式的领悟方法！");
			command("sigh");
			command("say 想当年我与太阳神战于九天之上，唉。。。，不提也罢。");
			me->set_temp("jueqing/binghun",1);
			return ("你先去找百花师姐，询问关于魔界之事！");
		}
		else
		{
			return ("赶紧动身吧，此行一切小心为上！");
		}
	}
}