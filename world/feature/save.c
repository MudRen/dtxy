// save.c

int save()
{
	string file;

/*
    if ( userp(this_object()) )
  {
          if ( this_object()->query("mud_age") < 1800 && !wizardp( this_object() )  )
                 {
             write("��վ�������½�id���������߰�Сʱ���ϲű��棬���в��㣬����¡�\n");
                          return 1 ;
                             }
  }
  */
	if( stringp(file = this_object()->query_save_file()) ) {
		assure_file(file+ __SAVE_EXTENSION__);
		return save_object(file);
	}
	return 0;
}

int restore()
{
	string file;

	if( stringp(file = this_object()->query_save_file()) )
		return restore_object(file);
	return 0;
}
