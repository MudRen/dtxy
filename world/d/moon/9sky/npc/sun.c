// tomcat
 
#include <ansi.h>

inherit NPC;
string ask_jueqing();
void create()
{
  set_name(HIR"太阳神"NOR, ({"taiyang shen", "sun"}));
   
  set("gender", "男性");
  set("age", 430);
  set("str", 100);
  set("per", 35);
  set("int", 30);
  set("cor", 50);
  set("cps", 40);
  set("combat_exp", 10000000);
  set_skill("spear", 600);
  set_skill("force", 600);
  set_skill("dodge", 600);
  set_skill("parry", 600);
  set_skill("unarmed", 600);
  set_skill("huoyun-qiang", 600);
  set_skill("literate", 600);
  set_skill("spells", 600);
  set_skill("pingtian-dafa", 600);
  set_skill("moshenbu", 600);
  set_skill("huomoforce", 600);
  set_skill("moyun-shou", 600);
  map_skill("force", "huomoforce");
  map_skill("spells", "pingtian-dafa");
  map_skill("unarmed", "moyun-shou");
  map_skill("spear", "huoyun-qiang");
  map_skill("parry", "huoyun-qiang");
  map_skill("dodge", "moshenbu");
  set("max_sen", 10000);
  set("max_kee", 10000);
set("force", 18000);
set("max_force", 9000);
set("mana",18000);
set("max_mana",9000);
set("daoxing",10000000);
set("force_factor", 450);
set("mana_factor", 451);
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
		(: perform_action, "spear", "lihuo" :),
  }) );
 set("inquiry",([
      "射日": (: ask_jueqing :),
      ]));
  set("family/family_name","火云洞");
  setup();
 
  carry_object("d/obj/weapon/spear/huomoqiang")->wield();
  carry_object("/d/obj/armor/jinjia")->wear();
}


string ask_jueqing()
{
	object me=this_player();
	if( me->query("can_go_sun") )
	{
		me->delete("can_go_sun");
		if( random(me->query("kar")) > 20 )
		{
			message_vision("\n$N对$n说：既然你如此诚心，日后如有需要，我一定劲力相助！\n",this_object(),me);
			me->set("accept/sun",1);
		}
		else
			message_vision("\n$N对$n说：你我缘分不够，日后你要好自为之！\n",this_object(),me);
		message_vision("\n$N也不再多说，一挥手$n晕晕乎乎来到了南城客栈！\n",this_object(),me);
		me->move("/d/city/kezhan");
		return ("往事不堪回首。。。");
	}
      	if( !me->query_temp("jueqing/sun") )
      	{
	      	me->move("/d/city/kezhan");
	      	return("你是怎么闯进来的？！");
	}
	else
	{
		command("sigh");
		me->set_temp("jueqing/sun",2);
		command("say 那时我们几个兄弟任性胡为，导致苍生蒙难，触怒了玉帝。");
		message_vision("$N说道：后来玉帝赐后羿九天神箭，西王母收嫦娥为弟子，传授天宫秘法。\n",this_object());
		message_vision("$N说道：再后来嫦娥如你一般，借助九天神箭的力量到了九天之外。\n",this_object());
		message_vision("$N说道：当时嫦娥一身白衣如雪，手提楚妃剑，那样子三界之中恐怕无人能比。\n",this_object());
		message_vision("$N说道：当时我们都看呆了，不过嫦娥修行日短，我们倒是不怕。\n",this_object());
		message_vision("$N说道：谁知嫦娥悟性过人，体质更是异于常人，所以她不怕九天神火，同时她借助天宫灵药修为突飞猛进，实是已经超出我们意料了。\n",this_object());
		message_vision("$N说道：嫦娥挥剑如舞，经过苦战，斩杀了我八个弟弟。只是每见她挥剑一次，我便爱她一分。\n",this_object());
		message_vision("$N说道：当她走到我面前的时候，已经无力再战了，只要我一个法术就能杀了她，为我八个弟弟报仇。\n",this_object());
		message_vision("$N说道：只是，只是，我最终还是下不了手，于是我将她送到了月宫，并给西王母传信。\n",this_object());
		message_vision("$N说道：虽然她体质异于常人，但是我们的修为也很厉害，所以她还是中了九天神火的火毒，也只有月宫才能让她活下去了。\n",this_object());
		message_vision("$N说道：数千年都过去了，也不知道她怎么样了。\n",this_object());
		me->command("say 我得到了冰魂，想必嫦娥姐姐的伤势已经好了吧。");
		message_vision("$N说道：那就好，当年我们对下界造成了那么大的伤害，唉，悔不该当初。。。\n",this_object());
		if( random(me->query("kar")) > 20 )
		{
			message_vision("\n$N沉默了一会，突然对$n说：日后，如果你需要帮忙，日间望空喊我一声，若我在附近，定会助你一臂之力！\n",this_object(),me);
			me->set("accept/sun",1);
		}
		message_vision("$N说道：我知道你此行就是了知道当年的经过，这里过于炎热对你身体不好，我还是早点送你回去吧。\n",this_object());
		message_vision("$N说道：数千年了，我一直背负这些，真的好累，今天说出来，轻松多了，还要多谢你了。\n",this_object());
		message_vision("$N说道：最后替我向他们两个送上祝福吧！\n",this_object());
		message_vision("\n$N也不再多说，一挥手$n晕晕乎乎来到了南城客栈！\n",this_object(),me);
		me->move("/d/city/kezhan");
		return ("往事不堪回首。。。");
	}
}