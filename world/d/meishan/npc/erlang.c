//erlang.c writted by Beeby. 07/30/2000

#include <ansi.h>

inherit NPC;
int begin_chasing();
void create()
{
        set_name("????????", ({"erlang zhenjun", "erlang", "zhenjun"}));
        set("long", "???ǳ????ѻ?Ӣ??ʥ???Ի??ޱߺŶ??ɡ?
?????˹?????Զ??????÷ɽ??ʥ?С?\n");
	set("looking", "?????忡ò???ã?????????Ŀ?й⡣");
        set("age", 28);
        set("attitude", "peaceful");
        set("gender", "????");
        set("title", "?ѻ???????");
        set("family/family_name","??????");
        set("str", 60);
        set("int", 40);
        set("per", 30);
	set("con", 30);
        set("max_kee",3000);
        set("max_sen", 3000);
        set("combat_exp", 10000000);
        set("daoxing", 10000000);

        set("force", 10000);
        set("max_force", 5000);
        set("mana", 10000);
        set("max_mana", 5000);
        set("force_factor", 250);
        set("mana_factor", 251);

        set("eff_dx", 800000);
        set("nkgain", 800);

        set_skill("unarmed",340);
	set_skill("dragonfight", 340);
	set_skill("parry",340);
	set_skill("dodge",340);
	set_skill("spear",340);
	set_skill("bawang-qiang",340);
	set_skill("force",340);
	set_skill("lengquan-force",340);
	set_skill("spells", 340);
	set_skill("baguazhou",340);
	set_skill("yanxing-steps", 340);
	map_skill("spells", "baguazhou");
	map_skill("force", "lengquan-force");
	map_skill("dodge", "yanxing-steps");
	map_skill("parry", "bawang-qiang");
	map_skill("spear","bawang-qiang");
	map_skill("unarmed", "dragonfight");
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "spear","meihua" :),
	}) );
        set("inquiry", ([ /* sizeof() == 4 */
  		"me" : (: begin_chasing :),
  		"here" : "?ҷ???????ּ????Ҫ?˱?׽?÷????칬????????ʥ??",
  		"name" : "???˶???????????Ҳ??",
  		"??????ʥ" : (: begin_chasing :),
	]) );

        setup();
        carry_object("/d/meishan/npc/obj/spear")->wield();
        carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/obj/drug/jinchuang")->set_amount(random(10));
}

void init()
{
	object me=this_object();
	object who=this_player();
	if (me->query("name") != "????????" && me->query_temp("chasing_status") && 
	environment(me)!=me->query_temp("last_env"))
	{
	   me->set("name","????????");
	   me->set("title","?ѻ???????");
	   message_vision(HIY"$N???????????һ?Σ???????????\n"NOR,me);
	}
	return ::init();
}
			
		     
void die()
{
	object who;
	object me=this_object();
	remove_call_out("check_status");
        if( environment() ) {
        message("sound", "\n\n??????ŭ??????ĪҪ???񣬴???????????״ȥ??\n\n", environment());
        message("sound", "\n?????????ϰ??ƣ??????????ŷ?ȥ??????\n\n", environment());
        command("drop all");
        }
        who = query_temp("last_damage_from");
        if( who->query_temp("kill/erlang") )
	{
		who->delete_temp("kill");
		if( random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("qingyun_known",1);
   			message("chat",HIC+"\n\n??"+HIW+"????ҥ??"+HIC+"?????ؿ?(ji yikao)??" + who->name() + "ɱ????????????ȴ???ն?Թ?????????????ŵ?֮????\n\n\n"NOR,users());
		}
		else
		{
			who->set("qingyun_cant",1);
			message("chat",HIC+"\n\n??"+HIW+"????ҥ??"+HIC+"?????ؿ?(ji yikao)??" + who->name() + "ɱ????????????ȴ?????ն?Թ????ϧδ???????????ŵ?֮????\n\n\n"NOR,users());
		}
	}
	if (query_temp("chasing_status")==5 && !query_temp("chasing_fail")
	    && query_temp("current_player"))
	{
	   who=query_temp("current_player");
	   who->set("dntg/erlang","done");
	   who->add("cor",2);
	   tell_object(who,HIW"?????????ѵĵ?ʶһ?????????˲??٣?\n"NOR);
	   CHANNEL_D->do_channel(me,"chat",who->query("name")+"??ĪҪ???񣬴???????????״ȥ??");
	} 

        destruct(this_object());
}

void kill_ob(object who)
{
	if (!query_temp("current_player"))
	  return ::kill_ob(who);
	if (query_temp("current_player")!=who)
	  set_temp("chasing_fail",1);
	return ::kill_ob(who);
}

int accept_fight(object who)
{		
	if (query_temp("chasing_status"))
	  {
	    if (query_temp("current_player")!=who)
	     return notify_fail("????????ҡ??ҡͷ????????????ʰ???????????Ӱɣ???\n");
	    else
	     kill_ob(who);
	  }
	return ::accept_fight(who);
}	
	  
	

int receive_damage(string arg,int damage,object me)
{
	if (this_object()->query_temp("no_damage"))
	   return 1;
	else return ::receive_damage(arg,damage,me);
}

int begin_chasing()
{
	object me=this_object(); 
	object who=this_player();
if (!userp(who))
{ 
command("fool");
command("say С????,С???Ұ?????????Ƥ,???͹???");
return 1;
}
	if (who->query("dntg/erlang") == "done" )
	 {
	 	command("shake");
	 	command("say ??λ"+RANK_D->query_respect(who)+"?Ĺ????Ѿ????̹??ˡ?\n");
	 	return 1;
	 }
if((int)who->query_skill("spells") < 300)
         {
  command("say ??ƾ??Ҳ??????????ʥ?\n");
                command("haha");
return 1;
}
	if (query_temp("chasing_status"))
	 {
		if (query_temp("current_player")==who)
		  command("say ???Թ?Ͷ????!");
		else
		  command("say ??ô????һ??????????????ʰ?㣡");
		return 1;
	 }
	command("look "+who->query("id"));
	command("jump");
	command("say ?????????㲻??????ȴ????????????????????Ҳ??");
	command("follow "+who->query("id"));
	me->set("max_kee",4000);
	me->set("max_sen",4000);
	me->set("eff_kee",4000);
	me->set("eff_sen",4000);
	me->set("kee",4000);
	me->set("sen",4000);
	me->set("force",4000);
	me->set("mana",4000);
	me->kill_ob(who);
	who->kill_ob(me);
	me->set_temp("current_player",who);
	me->set_temp("chasing_status",0);
	me->set_temp("no_damage",1);
	remove_call_out("check_status");
	call_out("check_status",1);
	return 1;
}

void check_status()
{
	object me=this_object();
	object who=query_temp("current_player");
	string *id_list;
	if (!who || who->is_ghost())
	 {  
	    message_vision("$N??Цһ????????ν??????ʥҲ???????˰?!??\n"+
	                  "ת??????һ?????ƻ?÷ɽȥ?ˡ?\n",me);
	    remove_call_out("check_sratus");
	    destruct(me);
	    return;
	 }
	if (me->query("eff_kee") < me->query("max_kee")*9/10 &&
	    present("jinchuang yao",me))
	   command("eat yao");
	if (me->query("kee") < me->query("eff_kee")*9/10 &&
	    me->query("force") > 0)
	   command("exert recover");
	if (me->query("sen") < me->query("eff_sen")*9/10 &&
	    me->query("force") > 0)
	   command("exert refresh");
	if (!present(who,environment(me)))
	 {
	   me->move(environment(who));
	   message_vision("$N???˹?????\n",me);
	 }
        if (id_list=who->query_temp("apply/id"))
	   switch (me->query_temp("chasing_status"))
	   {
	   	case 0:if (member_array("maque",id_list)!=-1 
	   	           && environment(me)->query("short")=="ɽ??") 
	   		{
	   		 message_vision(HIY"$N?????ھ???????ԣ?ҡ??һ?䣬????һֻȸӥ??\n"NOR,me);
	   		 me->set_temp("chasing_status",1);
	   		 me->set("name","ȸӥ");
	   		 me->set("title","");
	   		 me->set_temp("last_env",environment(me));
	   		 break;
	   		}
	   	case 1:if (member_array("ci hu",id_list)!=-1
	   		   && environment(me)->query("short")=="СϪǰ")
	   		{
	   		 message_vision(HIY"$N?????ھ???????ԣ?ҡ??һ?䣬????һֻ???ף?\n"NOR,me);
	   		 me->set_temp("chasing_status",2);
	   		 me->set("name","????");
	   		 me->set("title","");
	   		 me->set_temp("last_env",environment(me));
	   		 break;
	   		}
	   	case 2:if (member_array("fish",id_list)!=-1
	   		&& environment(me)->query("short")=="СϪ")
	   		{
	   		 message_vision(HIY"$N?????ھ???????ԣ?ҡ??һ?䣬????һֻ??ӥ??\n"NOR,me);
	   		 me->set_temp("chasing_status",3);
	   		 me->set("title","");
	   		 me->set("name","??ӥ");
	   		 me->set_temp("last_env",environment(me));
	   		 break;
	   		}
	   	case 3:if (member_array("shui she",id_list)!=-1
	   		&& environment(me)->query("short")=="СϪ")
	   		{
	   		 message_vision(HIY"$N?????ھ???????ԣ?ҡ??һ?䣬????һֻ?Һף?\n"NOR,me);
	   		 me->set_temp("chasing_status",4);
	   		 me->set("name","?Һ?");
	   		 me->set("title","");
	   		 me->set_temp("last_env",environment(me));
	   		 break;
	   		}
	   	case 4:if (member_array("hua bao",id_list)!=-1
	   		 && environment(me)->query("short")=="СϪǰ")
	   		{
	   		 me->delete_temp("no_damage");
	   		 me->set_temp("chasing_status",5);
	   		}
	   }
	 
	remove_call_out("chech_status");
	call_out("check_status",1);
	return;
}   
