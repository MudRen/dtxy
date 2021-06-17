//auto_move.h modify by gump

inherit F_LOCATION;
#define AUTO_MOVE_TIME	120
#define AUTO_DEST_TIME	9*60
void auto_disapper();

void auto_move()
{
	string place, desc;
	object me, master;
	mapping room;///
	
	me=this_object();
	master=query("master");
	if(!objectp(master))
	{
		auto_disapper();
		return;
	}
	do{
//		place=random_location();
		room=LOCATIOND->random_location();
		place=room["file"];
	}while(sscanf(place, "[%s]%s", desc, place)!=2);
	if(!query("move_msg/out"))
		message_vision("$N�����뿪��\n", me);
	else message_vision(query("move_msg/out"), me);
	me->move(place);
	if(!query("move_msg/in"))
		message_vision("$N���˹�����\n", me);
	else message_vision(query("move_msg/in"), me);
	call_out("auto_move", AUTO_MOVE_TIME);
	return;
}

void auto_disapper()
{
	object me;
	
	me=this_object();
	if(!query("move_msg/dis"))
		message_vision("$N�����뿪��\n", me);
	else message_vision(query("move_msg/dis"), me);
	destruct(me);
	return;
}


int accept_object(object who, object ob)
{
	object me, master, silver;
	string type, reward_msg,msg;
	int pot, reward, times;
	
	me=this_object();
	type=query("type");
	
	if(!objectp(master=query("master")) || master!=who)
		return 0;
	if(ob->query("master")!=who)
		return 0;
	if(ob->query("target")!=me)
		return 0;
	command("thank");
	who->delete("g_quest/"+type+"/quest");
	times=who->query_temp("g_quest/"+type);
	times++;
	switch(type)
	{
/*		case "captor":
		pot=10+random(10);
		reward=50+random(50);
		pot=pot*times/2+random(pot*times/2);
		reward=reward*times/2+random(reward*times/2);
		who->add("potential", pot);
		who->add("wuxue_exp", reward);
		who->add("g_quest/reward/potential", pot);
		who->add("g_quest/reward/wuxue", reward);
		reward_msg=sprintf("��%s��ȫ�͵����õ���%s����ѧ��%s��Ǳ�ܡ�\n",
			ob->name(1), chinese_number(reward), chinese_number(pot));
		tell_object(who, "��ϲ�㣡\n��"+reward_msg);
		MONITOR_D->report_system_object_msg(who, reward_msg);
		break;*/
		case "dancer":
                pot=20+random(20);
		reward=200+random(100);
		pot=pot*times/2+random(pot*times/2);
		reward=reward*times/2+random(reward*times/2);
		who->add("potential", pot);
		who->add("combat_exp", reward);
		who->add("g_quest/reward/potential", pot);
		who->add("g_quest/reward/daoxing", reward);
		reward_msg=sprintf("��%s��ȫ�͵����õ���%s���к�%s��Ǳ�ܡ�\n",
			ob->name(1), COMBAT_D->chinese_daoxing(reward),
			chinese_number(pot));
		tell_object(who, "��ϲ�㣡\n��"+reward_msg);
		MONITOR_D->report_system_object_msg(who, reward_msg);
		msg=sprintf("��%s"+MAG"��ȫ�͵����õ���%s���к�%s��Ǳ�ܡ�\n",
			ob->name(1), COMBAT_D->chinese_daoxing(reward),
			chinese_number(pot));
		message("channel:es",MAG+"������ׯ������(Hong niang)��"+who->query("name")+msg+"\n"+NOR,users());
		break;
		case "captor":
                pot=10+random(10);
		reward=50+random(20);
		pot=pot*times/2+random(pot*times/2);
		reward=reward*times/2+random(reward*times/2);
		who->add("potential", pot);
		silver=new(SILVER_OB);
		silver->set_amount(reward);
		silver->move(who);
		who->add("g_quest/reward/potential", pot);
		who->add("g_quest/reward/silver", reward);
		reward_msg=sprintf("��%s��ȫ�͵����õ���%s��������%s��Ǳ�ܵĳ��͡�\n",
			ob->name(1), chinese_number(reward), chinese_number(pot));
		tell_object(who, "��ϲ�㣡\n��"+reward_msg);
		MONITOR_D->report_system_object_msg(who, reward_msg);
		msg=sprintf("��%s"+WHT"��ȫ�͵����õ���%s��������%s��Ǳ�ܵĳ��͡�\n",
			ob->name(1), chinese_number(reward), chinese_number(pot));
		message("channel:chat",WHT+"����������̫ƽ����(Taiping gongzhu)��"+who->query("name")+msg+"\n"+NOR,users());
		break;
	}
	who->add_temp("g_quest/"+type,1);
	if(who->query_temp("g_quest/"+type)>9)
		who->set_temp("g_quest/"+type,0);
	remove_call_out("auto_disapper");
	call_out("auto_disapper", 1);
	return 1;
}

void die()
{
	auto_disapper();
}

void unconcious()
{
	die();
}


