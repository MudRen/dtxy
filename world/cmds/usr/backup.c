// backup.c by canoe

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object link_ob;
	//string file;
	seteuid(getuid());

	if( !objectp(link_ob = me->query_temp("link_ob")) )
		return notify_fail("�㲻�Ǿ����������߽��룬���ܴ��档\n");
		
 if( (time()-me->query("last_backup")) < 60
||time()-me->query("last_save")<60 )        
		return notify_fail("��ٵ�ſ��Դ��档\n");
    write(
		"��Ϊ�������ݹ��ڵ��������ݰ�ȫ���⣬������Ҫȷ����Ĺ������롣\n"
		"���������Ĺ������룺");
	input_to("check_password", 1, me);
	return 1;
	}

private mixed check_password(string passwd, object me)
{
	object link_ob;
	string old_pass;
        object* inv;
	int     i; 
	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("super_password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("�����������\n");
		return;
	}
else 
    me->set("last_backup",time());
    
	if( (int)link_ob->save() && (int)me->save() && (int)me->backup()) {
		// backup for fabao

		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); ++i)  {
		   if( inv[i]->query("owner_id") == getuid(me) && 
		   inv[i]->query("series_no") )   {
			   inv[i]->unequip();
			   if( !(int)inv[i]->backup() )   {
		           write("\n����ʧ�ܡ�\n");
                   write("\n����ʧ�ܡ�\n");
		           return 0;
			   }
		   }
		}

        write("\n��ϲ������������ϡ�\n");
        write("��ϲ��������ϡ�\n");
		return 1;
	} else {
		write("\n����ʧ�ܡ�\n");
        write("\n����ʧ�ܡ�\n");
		return 0;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ��backup

���ݵ���������ĵ�������Ī��������˺��󣬿�Ҫ����ʦ�ָ���
HELP
	);
	return 1;
}
