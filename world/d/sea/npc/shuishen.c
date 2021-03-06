#include <ansi.h>

inherit NPC;
inherit F_MASTER;


void create()
{
        set_name("妈祖", ({"ma zu","mazu","haishen","niangniang"}));

	set("long","传说中守护海界的女神，保佑海民出海平安．\n");
    set("gender", "女性");
       set("age", 30);
       set("title", HIB"海神娘娘"NOR);
       set("class","dragon");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("combat_exp", 10000000);
       set("daoxing", 10000000);
       set("per", 40);
       set("str", 1000);
       set("max_kee", 6000);
       set("max_gin", 6000);
       set("max_sen", 6000);
       set("force", 16000);
       set("max_force", 8000);
       set("force_factor", 300);
       set("max_mana", 8000);
       set("mana", 16000);
       set("mana_factor", 400);
       set_skill("huntian-hammer", 300);
       set_skill("hammer", 300);
       set_skill("literate", 300);
       set_skill("unarmed", 300);
       set_skill("dodge", 300);
       set_skill("force", 300);
       set_skill("parry", 300);
       set_skill("fork", 300);
       set_skill("spells", 300);
	set_skill("seashentong", 300);
	set_skill("dragonfight", 300);
	set_skill("dragonforce", 250);
	set_skill("fengbo-cha", 300);
	set_skill("dragonstep", 300);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
	set("cfpl_known",2);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: cast_spell, "freez" :),
                (: exert_function, "shield" :),
                (: perform_action, "unarmed", "sheshen" :),
                (: perform_action, "unarmed", "shenglong" :),
                (: perform_action, "fork", "fengbo" :),
                (: perform_action, "fork", "cfpl" :),
                }) );
        create_family("东海龙宫", 1, "水族");
	set_temp("apply/armor",250);
	set_temp("apply/damage",250);
	setup();

        carry_object("/d/sea/obj/longpao")->wear();
        carry_object("/d/sea/obj/tuotiancha")->wield();
}

void attempt_apprentice(object ob)
{	
       
       
       if (ob->query("obstacle/number") < 26) {
        command("say 这位" + RANK_D->query_respect(ob) + "你还是先出去闯荡一番吧！\n");
        command("sigh");
        return;
        }

      if (((int)ob->query("daoxing") < 1000000 )) {
         command("say " + RANK_D->query_rude(ob) + "这点三脚猫的把式怎么能拜我为师？回去练练把!");
         return;
       }
       
       
       command("smile");
        command("say 难得" + RANK_D->query_respect(ob) +
		"有此心志，还望日后多加努力，为我水族争光。\n");
        command("recruit " + ob->query("id") );
	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
              ob->set("class", "dragon");
        ob->set("title", HIB"妈祖娘娘传人"NOR);
}

void init()
{
	::init();
	add_action("do_lingwu", "lingwu");
}
string do_lingwu()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("你三心二意无法领会龙宫绝学。\n");
	if(me->query("family/family_name") != "东海龙宫" )
                return ("你不是我龙宫弟子!!\n");
        if(me->query("cfpl_cant"))
      		return ("你的资质不适合学习乘风破浪！");
        if( me->query("cfpl_known") > 1 )
      		return ("乘风破浪的口诀你都已经知道了啊！");
      	if( !me->query("cfpl_lingwu") )
      		return ("乘风破浪也需要顺序渐进，你还是先去找龙女，鲸无敌吧！");
      	if( me->query_temp("lingwu") )
      		return ("你正在领悟啊！");
      	if( !me->query("cfpl_known") )
      	{
	      	if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
	                return ("你的叉法级别还不够！\n");
	        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
	                return ("你的锤法级别还不够！\n");
	        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
	                return ("你的掌法级别还不够！\n");
	}
	else
	{
		if(me->query_skill("fork", 1) < 300 || me->query_skill("fengbo-cha", 1) < 300)
	                return ("你的叉法级别还不够！\n");
	        if(me->query_skill("hammer", 1) < 300 || me->query_skill("huntian-hammer", 1) < 300)
	                return ("你的锤法级别还不够！\n");
	        if(me->query_skill("unarmed", 1) < 300 || me->query_skill("dragonfight", 1) < 300)
	                return ("你的掌法级别还不够！\n");
	}
      	me->start_busy(20);
      	me->set_temp("lingwu",1);
      	message_vision(HIC"\n$N盘膝静坐，开始领悟乘风破浪！\n"NOR,me);
      	if( !me->query("cfpl_known") )
      	{
      		message_vision(HIC"\n妈祖说道：风波十二叉是我龙宫数辈人，依照海水变息流动之理创出来的。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：虽然我龙宫中人个个都会几招，但是领悟其中精髓的，数百年来寥寥无几。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：既然你已经领悟到了风波十二叉的精髓，现在你只要将所领悟到的融会贯通就可以了。\n"NOR,me);
      		
      		if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
      			call_out("finish1",10,me);
      		else
      			call_out("finish2",10,me);
      	}
      	else
      	{
      		message_vision(HIC"\n妈祖说道：风波十二叉是我龙宫数辈人，依照海水变息流动之理创出来的。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：而混天锤法，据说是依照盘古大帝开天所用的混沌一破演变而来。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：虽然你已经领悟了风波十二叉和混天锤法的精髓。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：但是锤乃重兵器，若是与战斗中仓促更换，就会给敌人可乘之机。\n"NOR,me);
      		message_vision(HIC"\n妈祖说道：你现在就是需要将各种武功融会贯通，使换招之间没有破绽。\n"NOR,me);
      		me->delete("cfpl_lingwu");
      		if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
      			call_out("finish1",10,me);
      		else
      			call_out("finish2",10,me);
      	}
      		
}

void finish1(object me)
{
	me->delete_temp("lingwu");
	if( !me->query("cfpl_known") )
	{
		me->set("cfpl_known",1);
		message_vision(HIC"\n$N静坐潜思多时，突然身边海水轻轻涌动。\n"NOR,me);
		message_vision(HIC"\n$N体内龙神真气，随之波动，先前在海底莽林中那种与海水融为一体的奇妙感觉再次涌现。\n"NOR,me);
		message_vision(HIC"\n$N以真气捕捉海水的灵气，慢慢形神交融。\n"NOR,me);
		message_vision(HIC"\n$N豁然明朗，风波十二叉的招式在你脑海中不停闪过，宛如你自己手持钢叉，顺流击刺。\n"NOR,me);
		message_vision(HIC"\n$N一声龙吟长身而起，海水绕在$N四周欢快的奔腾。\n"NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗妈祖（ma zu）："+ me->name()+"顿悟风波十二叉精髓，终于掌握了"+HIY"乘风破浪"+HIC"前四式！\n"NOR,users());
		tell_object(me,"你耳边传来妈祖的声音：以你目前的能力还不能化叉为锤，若日后有成再来找我。\n");
		message_vision(HIC"\n一股水流从$N脚底涌起，$N消失不见了！\n"NOR,me);
		me->move("/d/sea/inside1");
		message_vision(HIC"\n突然一阵水波涌起，$N从中走了出来！！\n"NOR,me);
	}
	else
	{
		me->set("cfpl_known",2);
		message_vision(HIC"\n$N静坐潜思多时，突然身边海水涌出一股暗流，想要将$N高高抛起。\n"NOR,me);
		message_vision(HIC"\n$N体内龙神真气一转，坐姿不变，顺着海水之力升至半空。\n"NOR,me);
		message_vision(HIC"\n$N忆起当日龙宫广场那惊天一击，周身血液沸腾，龙神真气再次急速运转膨胀。\n"NOR,me);
		message_vision(HIC"\n$N豁然顿悟，半空中长身而起，手舞足蹈间，将龙宫各种武功交替使出，出招时浑然天成，不露半分破绽。\n"NOR,me);
		message_vision(HIC"\n$N一声龙吟，身形突然倒转而下，有如流星下坠，其快绝伦，运起龙神真气直击而下。\n"NOR,me);
		message_vision(HIC"\n$N只觉撞在一股柔水般的内力之上，几个起落化解了$N的劲力，$N一个翻身顺势落下。\n"NOR,me);
		message_vision(HIC"\n只见妈祖含笑望着$N，$N躬身下拜。\n"NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗妈祖（ma zu）："+ me->name()+"终于将龙宫武学融会贯通，完全掌握了龙宫绝学"+HIY"乘风破浪"+HIC"！\n"NOR,users());
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗敖广（ao guang）：哈哈，今后看谁还敢来龙宫撒野？！\n"NOR,users());
		tell_object(me,"你耳边传来妈祖的声音：切记，乘风破浪威力绝伦，多行善举，万万不可用来作恶。\n");
		message_vision(HIC"\n一股水流从$N脚底涌起，$N消失不见了！\n"NOR,me);
		me->move("/d/sea/inside1");
		message_vision(HIC"\n突然一阵水波涌起，$N从中走了出来！！\n"NOR,me);
	}
	return;	
}

void finish2(object me)
{
	me->delete_temp("lingwu");
	me->delete("cfpl_lingwu");
	me->set("cfpl_cant",1);
	message_vision(HIC"\n$N潜思多时，头脑中一片混乱，四周海水波动不已，$N终不能再次体会到其中灵韵。\n"NOR,me);
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗妈祖（ma zu）："+ me->name()+"终不能领会龙宫武学精髓，与"+HIY"乘风破浪"+HIC"擦身而过，可惜可叹！\n"NOR,users());
	command("sigh");
	message_vision(HIC"\n妈祖念了个口诀，素手一挥！\n"NOR,me);
	message_vision(HIC"\n一股水流从$N脚底涌起，$N消失不见了！\n"NOR,me);
	me->move("/d/sea/inside1");
	message_vision(HIC"\n突然一阵水波涌起，$N从中走了出来！！\n"NOR,me);
	return;	
}