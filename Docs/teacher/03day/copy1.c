

int main(int argc,char **argv)
{

	argv[1]  as  src file
	argv[2]  as  dst file

	creat(argv[2])

	open(src file)
	open(dst file)


	ret = read(src file, buf[1024])
	write(dst,buf,ret)

	close(1)
	close (2)
}
