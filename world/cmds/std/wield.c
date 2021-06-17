// wield.c

inherit F_CLEAN_UP;

int do_wield(object me, object ob);
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

	if( !arg ) return notify_fail("��Ҫװ��ʲô������\n");

	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wield(me, inv[i]) ) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n");

	if( ob->query("equipped") )
		return notify_fail("���Ѿ�װ�����ˡ�\n");

	return do_wield(me, ob);
}

int do_wield(object me, object ob)
{
	string str;
	int i, dx, zs;
    if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
		destruct(ob);
		return notify_fail("�´α���͵���˵Ķ�����\n");
	}
	
	if( me->query_temp("No_Wield") )
		return notify_fail("��ԭ�����֣������ٳֱ�����\n");
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
			return notify_fail("�����Ϊ�������޷�ʹ����˸߼���������\n");
		/*for(i=0;i<sizeof(tianfu);i++)
		{
			if( ob->query("wield/"+tianfu[i][0]) > 0 && ob->query("wield/"+tianfu[i][0]) > me->query(tianfu[i][0]) )
			{
				return notify_fail("���"+tianfu[i][1]+"�������޷�ʹ����˸߼���������\n");
			}
		}*/
	}
	if( ob->wield() ) {
			// added by emotion for new equippment system
		if ( ob->is_newitem() && ob->is_weapon() ) {
                     if ( ob->query("previous_holder") && ob->query("previous_holder") != me->query("id" ) )
			ob->set_item_attr("op_exp", 0); 
		     ob->set_item_attr("previous_holder", me->query("id" )); 
                }   // end -- emotion
		if( !stringp(str = ob->query("wield_msg")) )
			str = "$Nװ��$n��������\n";
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��wield|zhuangbei <װ������>
 
���ָ������װ��ĳ����Ʒ������, �����Ҫӵ��������Ʒ.
 
HELP
    );
    return 1;
}
