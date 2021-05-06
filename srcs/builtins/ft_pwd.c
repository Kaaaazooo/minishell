int	ft_pwd(void)
{
	char	buf[4096];

	getcwd(buf, 4096);
	printf("%s\n", buf);
	return (0);
}
