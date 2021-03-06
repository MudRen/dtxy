// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);
mixed *tianfu = ({
			({"str","体格"}),
			({"con","根骨"}),
			({"spi","灵性"}),
			({"kar","福缘"}),
			({"cps","定力"}),
			({"cor","胆识"}),
			({"per","容貌"}),
			({"int","悟性"}),
		 });
int main(object me, string arg)
{
	object ob, *inv;
	int i, count;

	if( !arg ) return notify_fail("你要穿戴什么？\n");

//	if ( time() - me->query_temp("last_time/remove") < 5 )
//                  return notify_fail("急什么？慢慢来。\n");

	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wear(me, inv[i]) ) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");

	if( ob->query("equipped") )
		return notify_fail("你已经装备着了。\n");

	return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
	string str;
	int i, dx, zs;
	if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
		destruct(ob);
		return notify_fail("下次别乱偷别人的东西。\n");
	}

	if( ob->query("No_Wear") )
		return notify_fail("这件衣服不能再穿了！\n");

//	if ( time() - me->query_temp("last_time/remove") < 6 )
//                  return notify_fail("急什么？慢慢来。\n");

	if( ob->query("female_only")
	&&	(string)me->query("gender") != "女性" )
		return notify_fail("这是女人的衣衫，你一个大男人也想穿，羞也不羞？\n");
	if( ob->query("wield/daoxing") )
	{
		dx = me->query("daoxing") / 1000;
		zs = me->query("lunhui_zhuanshi");
		if(!zs)
		{
			if(dx > 10000)
				dx = 10000;
		}
		else if(zs < 5)
		{
			dx += zs * 10000;
			if(dx > (zs + 1) * 10000)
			{
				dx = (zs + 1) * 10000;
			}
		}
		else
		{
			dx += zs * 10000;
		}
		if(wizardp(me))
			tell_object(me, "dx = " + dx + ",zs = " + zs + ", need = " + ob->query("wield/daoxing") + "\n");
		if( dx < ob->query("wield/daoxing") )
			return notify_fail("你的修为不够，无法使用如此高级的防具！\n");
		/*for(i=0;i<sizeof(tianfu);i++)
		{
			if( ob->query("wield/"+tianfu[i][0]) > 0 && ob->query("wield/"+tianfu[i][0]) > me->query(tianfu[i][0]) )
			{
				return notify_fail("你的"+tianfu[i][1]+"不够，无法使用如此高级的防具！\n");
			}
		}*/
	}
	if( ob->wear() ) {
		if( !stringp(str = ob->query("wear_msg")) )
			switch( ob->query("armor_type") ) {
				case "cloth":
				case "armor":
				case "boots":
				case "surcoat":
					str = YEL "$N穿上一" + ob->query("unit") + "$n。\n" NOR;
					break;
				case "head":
				case "neck":
				case "wrists":
				case "finger":
				case "hands":
					str = YEL "$N戴上一" + ob->query("unit") + "$n。\n" NOR;
					break;
				case "waist":
					str = YEL "$N佩上一" + ob->query("unit") + ob->query("name") + "。\n" NOR;
					break;
				default:
					str = YEL "$N装备$n。\n" NOR;
			}
		message_vision(str, me, ob);
		me->set_temp("last_time/wear",time());
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
指令格式：wear|chuan <装备名称>

这个指令让你装备某件防具。

HELP
    );
    return 1;
}
