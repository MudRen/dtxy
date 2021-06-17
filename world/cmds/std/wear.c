// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);
mixed *tianfu = ({
			({"str","���"}),
			({"con","����"}),
			({"spi","����"}),
			({"kar","��Ե"}),
			({"cps","����"}),
			({"cor","��ʶ"}),
			({"per","��ò"}),
			({"int","����"}),
		 });
int main(object me, string arg)
{
	object ob, *inv;
	int i, count;

	if( !arg ) return notify_fail("��Ҫ����ʲô��\n");

//	if ( time() - me->query_temp("last_time/remove") < 5 )
//                  return notify_fail("��ʲô����������\n");

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
		return notify_fail("������û������������\n");

	if( ob->query("equipped") )
		return notify_fail("���Ѿ�װ�����ˡ�\n");

	return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
	string str;
	int i, dx, zs;
	if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
		destruct(ob);
		return notify_fail("�´α���͵���˵Ķ�����\n");
	}

	if( ob->query("No_Wear") )
		return notify_fail("����·������ٴ��ˣ�\n");

//	if ( time() - me->query_temp("last_time/remove") < 6 )
//                  return notify_fail("��ʲô����������\n");

	if( ob->query("female_only")
	&&	(string)me->query("gender") != "Ů��" )
		return notify_fail("����Ů�˵���������һ��������Ҳ�봩����Ҳ���ߣ�\n");
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
			return notify_fail("�����Ϊ�������޷�ʹ����˸߼��ķ��ߣ�\n");
		/*for(i=0;i<sizeof(tianfu);i++)
		{
			if( ob->query("wield/"+tianfu[i][0]) > 0 && ob->query("wield/"+tianfu[i][0]) > me->query(tianfu[i][0]) )
			{
				return notify_fail("���"+tianfu[i][1]+"�������޷�ʹ����˸߼��ķ��ߣ�\n");
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
					str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
					break;
				case "head":
				case "neck":
				case "wrists":
				case "finger":
				case "hands":
					str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
					break;
				case "waist":
					str = YEL "$N����һ" + ob->query("unit") + ob->query("name") + "��\n" NOR;
					break;
				default:
					str = YEL "$Nװ��$n��\n" NOR;
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
ָ���ʽ��wear|chuan <װ������>

���ָ������װ��ĳ�����ߡ�

HELP
    );
    return 1;
}
