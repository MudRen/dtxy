//礼物使者，先写个简单的
inherit NPC;
#include <ansi.h>

mixed attr_list = ({"int", "str", "con", "spi", "per", "kar", "cps", "cor"});

int give_gift();
int give_08gift();
int give_seven();
int remove_questfail();
int give_2013();
int give_christmas();
int give_chunjie();
void create()
{
	set_name("礼物使者", ({"liwu shizhe","shizhe"}));
   	set ("long", @LONG

大唐礼物使者，你就去问问(ask)她关于礼物(gift)的消息。
LONG);
	set("gender", "女性");
    	set("title",HIM"有礼走遍天下"NOR);
        set("age", 21);
        set("per", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
	set("inquiry", ([
		"解密机会一":(:give_gift:),
		"解密机会二":(:give_08gift:),
		//"七夕":(:give_seven:),
		//"元旦":(:give_2013:),
		//"圣诞快乐":(:give_christmas:),
		"春节快乐":(:give_chunjie:),
	]));
        setup();
}

string get_chinese_gift(string gift) {
        switch(gift) {
                case "int":
                        return "悟性";
                        break;
                case "str":
                        return "力量";
                        break;
                case "con":
                        return "根骨";
                        break;
                case "spi":
                        return "灵性";
                        break;
                case "per":
                        return "容貌";
                        break;
                case "kar":
                        return "福缘";
                        break;
                case "cps":
                        return "定力";
                        break;
                case "cor":
                        return "勇气";
                        break;
                default:
                        return "不认识" + gift;
                        break;
        }
}

int remove_questfail()
{
	object who = this_player();
	int f = 0;
switch (who->query("family/family_name"))
        {
        	case "陷空山无底洞":
                { 
                	if( who->query("daojian_cant") )
                	{
                		who->delete("daojian_cant");
                		f = 1;
                	}
                        break;
		}
		case "将军府":
                { 
                	if( who->query("kai_cant") )
                	{
                		who->delete("kai_cant");
                		f = 1;
                	}
                        break;
		}
		case "五庄观":
                { 
                	if( who->query("wuxing_cant") )
                	{
                		who->delete("wuxing_cant");
                		f = 1;
                	}
                        break;
		}
		case "火云洞":
                { 
                	if( who->query("huohun_cant") )
                	{
                		who->delete("huohun_cant");
                		f = 1;
                	}
                        break;
		}
		case "南海普陀山":
                { 
                	if( who->query("fmtd_cant") )
                	{
                		who->delete("fmtd_cant");
                		f = 1;
                	}
                        break;
		}
		case "阎罗地府":
                { 
                	if( who->query("jingtian_cant") )
                	{
                		who->delete("jingtian_cant");
                		f = 1;
                	}
                        break;
		}
		case "大雪山":
                { 
                	if( who->query("piaoxue_cant") )
                	{
                		who->delete("piaoxue_cant");
                		f = 1;
                	}
                        break;
		}
		case "东海龙宫":
                { 
                	if( who->query("cfpl_cant") )
                	{
                		who->delete("cfpl_cant");
                		f = 1;
                	}
                        break;
		}
		case "方寸山三星洞":
                { 
                	if( who->query("fangcun/panlong_qiansi_finish") == 1 && who->query("fangcun/panlong_noway") )
                	{
                		who->delete("fangcun/panlong_qiansi_finish");
                		who->delete("fangcun/panlong_noway");
                		f = 1;
                	}
                	else if( who->query("fangcun/panlong_nowaylingtai") )
                	{
                		who->delete("fangcun/panlong_nowaylingtai");
                		f = 1;
                	}
                        break;
		}
		case "盘丝洞":
                { 
                	if( who->query("qingyun_cant") )
                	{
                		who->delete("qingyun_cant");
                		f = 1;
                	}
                        break;
		}
		case "三界散仙":
                { 
                	if( who->query("icefire_cant") )
                	{
                		who->delete("icefire_cant");
                		f = 1;
                	}
                        break;
		}
		case "月宫":
                { 
                	if( who->query("jueqing_cant") )
                	{
                		who->delete("jueqing_cant");
                		f = 1;
                	}
                	else if( who->query("jueqing_known") ==2 && !who->query("accept/sun") )
                	{
                		who->set("can_go_sun",1);
                		f = 1;
                	}
                        break;
		}
		case "昆仑山玉虚洞":
                { 
                	if( who->query("quzhu_cant") )
                	{
                		who->delete("quzhu_cant");
                		f = 1;
                	}
                        break;
		}
		case "蜀山派":
                { 
                	if( who->query("sword_cant") )
                	{
                		who->delete("sword_cant");
                		f = 1;
                	}
                        break;
		}
	}
	return f;
}

int give_gift()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say 小畜生回去多多修炼！");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 1000000 )
	{
		command("say 你修为不够，受不了这份礼物！");
	  	return 1;
	}
	if( who->query("gift/20061001") == "got" )
	{
		message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
	       	command("say 礼物只有一份！领过就不再给了！");
	  	return 1;
	}
	f = remove_questfail();
	if( f )
	{
		who->set("gift/20061001","got");
		message_vision(HIR"$N手一指，$n觉察到身体发生了一些神奇的变化。\n"NOR,this_object(),who);
		return 1;
	}
	message_vision(HIR"$N掐指一算，懊恼的对$n说道：解密没失败，要什么礼物。\n"NOR,this_object(),who);
	return 1;
}

int give_08gift()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say 小畜生回去多多修炼！");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say 你修为不够，受不了这份礼物！");
	  	return 1;
	}
	if( who->query("gift/20080101") == "got" )
	{
		message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
	       	command("say 礼物只有一份！领过就不再给了！");
	  	return 1;
	}
	f = remove_questfail();
	if( f )
	{
		who->set("gift/20080101","got");
		message_vision(HIR"$N手一指，$n觉察到身体发生了一些神奇的变化。\n"NOR,this_object(),who);
		return 1;
	}
	message_vision(HIR"$N掐指一算，懊恼的对$n说道：解密没失败，要什么礼物。\n"NOR,this_object(),who);
	return 1;
}

int give_seven()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say 小畜生回去多多修炼！");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say 你修为不够，受不了这份礼物！");
	  	return 1;
	}
	if( who->query("gift_exp/20110707") == "got" )
	{
		message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
	       	command("say 礼物只有一份！领过就不再给了！");
	  	return 1;
	}
	f = remove_questfail();
	who->set("gift_exp/20110707","got");
	message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "前来领取七夕礼物，大唐西游祝愿天下有情人终成眷属！\n\n"NOR,users());
	if( f )
	{
		message_vision(HIR"$N对$n说道：大唐西游祝你七夕快乐，天上月老赐你解密机会一次。\n"NOR,this_object(),who);
		return 1;
	}
	else
	{
		message_vision(HIR"$N对$n说道：恭喜你神功大成，大唐西游在七夕之日，特备薄礼一份。\n"NOR,this_object(),who);
		write(HIY"你得到了，100年道行，100000武学。\n"NOR);
		who->add("daoxing",100000);
		who->add("combat_exp",100000);
	}
	return 1;
}

int give_2013() {

object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say 小畜生回去多多修炼！");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say 你修为不够，受不了这份礼物！");
	  	return 1;
	}
	if( who->query("gift_exp/20130101") == "got" )
	{
		message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
	       	command("say 礼物只有一份！领过就不再给了！");
	  	return 1;
	}
	f = remove_questfail();
	who->set("gift_exp/20130101","got");
	message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "前来领取元旦礼物，大唐西游祝大家新年快乐！\n\n"NOR,users());
	if( f )
	{
		message_vision(HIR"$N对$n说道：大唐西游祝你新年快乐并且赐你解密机会一次。\n"NOR,this_object(),who);
		return 1;
	}
	else
	{
		message_vision(HIR"$N对$n说道：恭喜你神功大成，大唐西游在新年之际，特备薄礼一份。\n"NOR,this_object(),who);
		who->add("daoxing",100000);
		who->add("combat_exp",100000);
                who->add("g_balance",50000);
		who->add("obstacle/rebirth",-1);
                write(HIY"你得到了，100年道行，100000武学，5万金票，1根毫毛。\n"NOR);
	}
	return 1;
}

int give_christmas()
{
	int f = 0;
	int size, i;
	object who=this_player();
	if(!userp(who))
        {
                command("hate");
                command("say 小畜生回去多多修炼！");
                command("qi");
                return 1;
        }
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
        {
                command("say 你修为不够，受不了这份礼物！");
                return 1;
        }
	if( who->query("gift_exp/20121225") == "got" )
        {
                message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 礼物只有一份！领过就不再给了！");
                return 1;
        }
	f = remove_questfail();
	who->set("gift_exp/20121225","got");
	message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "领取圣诞礼物，大唐西游祝大家圣诞快乐！\n\n"NOR,users());
	if(!random(10))
	{
		size = sizeof(attr_list);
		i = random(size);
		who->add(attr_list[i], 1);
		message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "获得意外大奖，" + HIW + get_chinese_gift(attr_list[i]) + HIC"一点！\n\n"NOR,users());
	}
	if( f )
	{
		message_vision(HIR"$N对$n说道：大唐西游祝你圣诞快乐并且赐你解密机会一次。\n"NOR,this_object(),who);
	}
	else
	{
		message_vision(HIR"$N对$n说道：恭喜你神功大成，大唐西游在新年之际，特备薄礼一份。\n"NOR,this_object(),who);
                who->add("daoxing",100000);
                who->add("combat_exp",100000);
                who->add("g_balance",50000);
                who->add("obstacle/rebirth",-1);
                write(HIY"你得到了，100年道行，100000武学，5万金票，1根毫毛。\n"NOR);
	}
	return 1;
}

int give_chunjie()
{
        int f = 0;
        int size, i;
        object who=this_player();
        if(!userp(who))
        {
                command("hate");
                command("say 小畜生回去多多修炼！");
                command("qi");
                return 1;
        }
        if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
        {
                command("say 你修为不够，受不了这份礼物！");
                return 1;
        }
        if( who->query("gift_exp/20130209") == "got" )
        {
                message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 礼物只有一份！领过就不再给了！");
                return 1;
        }
        f = remove_questfail();
        who->set("gift_exp/20130209","got");
        message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "领取圣诞礼物，大唐西游祝大家春节快乐！\n\n"NOR,users());
        if(!random(7))
        {
                size = sizeof(attr_list);
                i = random(size);
                who->add(attr_list[i], 1);
                message("chat",HIC+"\n\n〖"+HIW+"大唐西游"+HIC+"〗礼物使者(liwu shizhe)：" + who->name() + "获得意外大奖，" + HIW + get_chinese_gift(attr_list[i]) + HIC"一点！\n\n"NOR,users());
        }
        if( f )
        {
                message_vision(HIR"$N对$n说道：大唐西游祝你春节快乐并且赐你解密机会一次。\n"NOR,this_object(),who);
        }
        else
        {
                message_vision(HIR"$N对$n说道：恭喜你神功大成，大唐西游在新年之际，特备薄礼一份。\n"NOR,this_object(),who);
                who->add("daoxing",10000);
                who->add("combat_exp",10000);
                who->add("g_balance",50000);
                who->add("potential",1000000);
                write(HIY"你得到了，10年道行，10000武学，5万金票，100万潜能。\n"NOR);
        }
        return 1;
}

