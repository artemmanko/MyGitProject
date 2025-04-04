Name:           sapper2
Version:        1.0
Release:        alt1
Summary:        A simple Igra game
Group:          Games/Arcade

License:        MIT
URL:            https://github.com/
Source0:        sapper2-1.0.tar

BuildRequires:  gcc-c++
Requires:       glibc

%description
A simple Minesweeper game implemented in C++.

%prep
%setup -q

%build
make

%files
/usr/bin/sapper2

%install
mkdir -p %{buildroot}/usr/bin
install -m 755 sapper2 %{buildroot}/usr/bin/sapper2

%changelog
* Thu Oct 26 2023 Manko <ivanov@example.com> - 1.0-1
- Initial package.
