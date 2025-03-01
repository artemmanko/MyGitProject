Name:           sapper1
Version:        1.0
Release:        1%{?dist}
Summary:        A simple Igra game
Group:          Games/Entertainment

License:        MIT
URL:            https://github.com/
Source0:        sapper1-1.0.tar

BuildRequires:  gcc-c++
Requires:       glibc

%description
A simple Minesweeper game implemented in C++.

%prep
%setup -q

%build
make

%files
/usr/local/bin/sapper1

%install
mkdir -p %{buildroot}/usr/local/bin
install -m 755 sapper1 %{buildroot}/usr/local/bin/sapper1

%changelog
* Thu Oct 26 2023 Manko <ivanov@example.com> - 1.0-1
- Initial package.
