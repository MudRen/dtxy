
// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//xiwangmu.c
inherit NPC;
inherit F_MASTER;
string ask_tian();
string ask_mieyao();
string ask_cancel();
string avenge();
string ask_jueqing();
string ask_jiutian();
void create()
{
       set_name("西王母", ({"xi wangmu", "xi", "wangmu","master"}));
       set("long", "西华至妙生伊川，穆王八骑访昆仑。\n");
       set("title", "月宫祖师");
       set("gender", "女性");
       set("age", 100);
       set("class","xian");
       set("attitude", "friendly");
       set("rank_info/respect", "老太太");
       set("cor", 30);
       set("per", 30);
   set("looking", "面色红润，满脸福态。");
       set("max_kee", 4500);
       set("max_gin", 800);
       set("max_sen", 4500);
       set("force", 4000);
       set("max_force", 2000);
       set("force_factor", 125);
       set("max_mana", 2000);
       set("mana", 4000);
       set("mana_factor", 100);
       set("combat_exp", 2000000);
       set_skill("literate", 150);
       set_skill("unarmed", 180);
       set_skill("dodge", 180);
       set_skill("force", 180);
       set_skill("parry", 180);
       set_skill("sword", 200);
       set_skill("spells", 190);
   set_skill("moonshentong", 180);
   set_skill("baihua-zhang", 180);
   set_skill("moonforce", 180);
   set_skill("snowsword", 200);
   set_skill("moondance", 150);
   map_skill("spells", "moonshentong");
   map_skill("unarmed", "baihua-zhang");
   map_skill("force", "moonforce");
   map_skill("sword", "snowsword");
   map_skill("parry", "snowsword");
   map_skill("dodge", "moondance");
   set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "mihun" :),
                (: cast_spell, "arrow" :)
        }) );
   set("inquiry", ([
          "复仇" : (: avenge :),
   //       "漫天飞雪" : (: ask_tian :),
                             "灭妖": (: ask_mieyao :),
           "cancel": (: ask_cancel :),
  	"绝情": (: ask_jueqing :),
  	"九天神箭": (: ask_jiutian :),
]));
create_family("月宫", 1, "红");
setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
        carry_object("/d/ourhome/obj/shoes")->wear();
}
void init()
{
add_action("do_kneel","kneel");
}
string avenge()
{
    object who=this_player(),killer,where;
    string killid;
    if((string)who->query("family/family_name")!="月宫")
        return ("你不是本派弟子，生死与我何干？");
    if(who->query("faith")<1000)
        return ("你在本门名望还不够，还需多加努力才行。");
    if(who->query("avenge/mud_age")>=who->query("death/mud_age"))
        return ("老身未闻死讯");
    killid=who->query("kill/last_killer");
    killer=find_living(killid);
    if(!killer||!userp(killer))
        return ("这个嘛，老身还得想一想");
    command("say 老身这就去为你抱仇。");
    who->set("avenge/mud_age",who->query("mud_age"));
    where=environment(who);
    tell_room(where,"只见西王母向空中一指：\n");
    tell_room(where,"护法天尊何在，速去将"+killer->query("name")+"抓来。\n");
    tell_room(environment(killer),"空中伸出一只大手将"+killer->query("name")+"抓走了。\n");
    killer->move(where);
    tell_room(where,killer->query("name")+"被从空中扔了下来。\n");
    command("say 大胆妖孽，胆敢杀害我月宫弟子");
    this_object()->kill_ob(killer);
    return("拿命来。");
} 
void attempt_apprentice(object ob)
{
   if ( !((string)ob->query("gender")=="女性")){
      command("shake");
          command("say 我们月宫只收女徒，这位" + RANK_D->query_respect(ob) + "还是另请高就吧。\n");
      return;
   }

   if ( (string)ob->query("family/family_name")=="月宫") {
   if (((int)ob->query("combat_exp") < 100000 )) {
   command("say " + RANK_D->query_respect(ob) +
"的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
       command("recruit " + ob->query("id") );
   return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"还是先去学些基础功夫吧。\n");
        return;
}
int accept_fight(object me)
{
   return 0;
}
/*
int accept_object()
{
       object me=this_object();
       object who=this_player();
      object ob;
    if(ob->query("id")=="houyilove"){
     if (((string)who->query("family/family_name")=="月宫")){
        who->set("kill_chang",1);
        write("西王母怒道：大胆嫦娥现在居然还与后羿仍有私情！当初饶他两人性命
，居然败我门风，哼，你去给我杀了嫦娥，老妇自有重赏!\n");
        call_out("destroy", 1, ob);
        return 1;
     }
     if (((string)who->query("family/family_name")!="月宫")){
        command("say 哼，我月宫的事什么时候轮到外人来管！？");
        me->kill_ob(who);
       who->kill_ob(me);
      call_out("destroy", 1, ob);
                        return 1;
     }
   }
    if(ob->query("id")=="paper"){
     if (((string)who->query("family/family_name")=="月宫")){
    who->set("kill_houyi",1);
        write("西王母怒道：大胆嫦娥现在居然还与后羿仍有私情！当初饶他两人性命
，居然败我门风，哼，你去给我杀了后羿,老妇自有重赏!\n");
        call_out("destroy", 1, ob);
        return 1;
     }
     if (((string)who->query("family/family_name")!="月宫")){
        command("say 哼，我月宫的事什么时候轮到外人来管！？");
        me->kill_ob(who);
       who->kill_ob(me);
      call_out("destroy", 1, ob);
           return 1;
     }
   }
   else return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
   }
*/
string ask_mieyao()
{
    object who=this_player();

    if((string)who->query("family/family_name")=="月宫") {
      command("smile "+who->query("id"));
      return "/d/obj/mieyao"->query_yao(who);
    }
    return ("非我门人,何故来此?\n");
}
int do_kneel()
{
    object who = this_player();
    if((string)who->query("family/family_name")!="月宫")
     return notify_fail(this_object()->query("name")+"说：你又不是仙家弟子，拜我干什么？\n");
   if("/d/obj/mieyao"->delete_mieyao(who)){
        command("say 既然如此，就算了吧，不过你没有完成任务，得受些惩罚！\n");
	who->add("faith",-5);
        message_vision("$N的忠诚度下降了！\n",who);
     }
}
string ask_tian()
{
    object who=this_player();
    if((string)who->query("family/family_name")!="月宫")
        return ("你不是本派弟子，怎么来晓得漫天飞雪?");
    if(who->query("faith")<1000)
        return ("你在本门名望还不够，还需多加努力才行。");
    who->set_temp("moon_tian",1);
        return ("你可以perform tian,也可以尝试perform mantian。");
}
 
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("没用的东西！");
}
else
{
     return ("你有任务吗？！");
}
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
      		return ("绝情中风回雪舞剑的口诀你都已经知道了啊！");
      	if(me->query("jueqing_cant"))
      		return ("你与绝情无缘！");
      	if(me->query("jueqing/xiwangmu"))
      		return ("绝情中风回雪舞剑的口诀你都已经知道了啊！");
      	if( !me->query_temp("jueqing/xiwangmu") )
      	{
      		me->set_temp("jueqing/xiwangmu",1);
      		command("sigh");
	      	command("say 问世间情为何物？直叫人生死相许！");
	      	command("say 我的几个好徒弟，都这么多年了还不能让我省心！");
	      	command("say 想当年，唉，不提也罢！");
	      	return("你既然有心，就去帮我看看西天门的织女吧！");
	}
	else if( me->query_temp("jueqing/xiwangmu") == 2 )
	{
		me->delete_temp("jueqing/xiwangmu");
		me->set("jueqing/xiwangmu",1);
		return("嗯，既然如此我也放心多了，这就传你风回雪舞剑的口诀！");
	}
      	else
      	{
      		return("快去西天门吧！");
      	}
}

string ask_jiutian()
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
      	if(me->query("can_go_sun"))
      	{
      		command ("say 既然你领悟了绝情的大部分奥秘，我就再帮你一次！");
      		message_vision("只见西王母一挥手，$N飘飘乎乎冲天而去！\n",me);
      		me->move("/d/moon/9sky/9sky");
      		return ("祝你好运！");
      	}
      	if( me->query_temp("jueqing/houyi") != 2 )
      	{
	      	return("你是什么人，竟然打听天宫宝物？！");
	}
	else if( !me->query_temp("jueqing/zhinv") )
	{
		me->set_temp("jueqing/zhinv",1);
		command ("say 九天神箭的事情，我还要推算一下。你闯入魔界，取得冰魂，大大削弱了魔界的实力，很好，很好！");
		command ("say 唉，这么多年来，为了让织女织造七彩云帛，可是苦了他们一双小儿女了。");
		command ("say 不如你趁此时机前去西天门告知织女，也好让他们团聚。");
		return("等你归来之时，九天神箭的下落，也该推算出来了！");
	}
	else if( me->query_temp("jueqing/zhinv") == 1 )
	{
		return("快去西天门，让织女牛郎也好早日团聚！");
	}
	else
	{
		command ("say 神器择主，其实九天神箭一直跟随在后羿的四周，不曾离开过！");
		command ("say 你也应该能够猜到吧，你要找的人就是后羿！");
		command ("say 九天神箭就埋在荆棘岭的石崖中，你去挖（dig）出来交给后羿！");
		command ("say 你看准时机，在他耳边大喝一声：“后羿，还不归来！”，他自然就能找回前世的记忆！");
		return ("等他清醒以后，你问问他是否愿意前来月宫吧！");
	}
}